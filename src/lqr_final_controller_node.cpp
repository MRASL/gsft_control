#include <ros/ros.h>

#include <mav_msgs/default_topics.h>
#include <nav_msgs/Odometry.h>
#include <mav_msgs/eigen_mav_msgs.h>
#include <mav_msgs/conversions.h>

#include <tf/tf.h>
#include <tf_conversions/tf_eigen.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>

#include "parameters.h"
#include "parameters_ros.h"
#include "common.h"

#include <gsft_control/LOE.h>
#include <gsft_control/VirtualControl.h>
#include <lqr_final.h>

lqr_finalModelClass gController;

bool gCommand_active;
bool gLOE_active;
Eigen::VectorXd gLOE(6);

void OdometryCallback(const nav_msgs::Odometry::ConstPtr &odom) {
  mav_msgs::EigenOdometry odometry;
  mav_msgs::eigenOdometryFromMsg(*odom, &odometry);

  gController.lqr_final_U.X[0 ]  = odometry.position_W.x();
  gController.lqr_final_U.X[1 ]  = odometry.position_W.y();
  gController.lqr_final_U.X[2 ]  = odometry.position_W.z();

  Eigen::Matrix3d R_W_B = odometry.orientation_W_B.toRotationMatrix();
  Eigen::Vector3d velocity_W =  R_W_B * odometry.velocity_B;

  gController.lqr_final_U.X[3 ]  = velocity_W.x();
  gController.lqr_final_U.X[4 ]  = velocity_W.y();
  gController.lqr_final_U.X[5 ]  = velocity_W.z();

  double psi, phi, teta;
  psi = atan2(R_W_B(1,0),R_W_B(0,0));
  phi = atan2(R_W_B(2,1),R_W_B(2,2));
  teta = asin(-R_W_B(2,0));

  gController.lqr_final_U.X[6 ]  = phi;
  gController.lqr_final_U.X[7 ]  = teta;
  gController.lqr_final_U.X[8 ]  = psi;

  Eigen::Matrix3d H;
  H << 1.0, sin(phi)*tan(teta), cos(phi)*tan(teta),
       0.0, cos(phi),           -sin(phi),
       0.0, sin(phi)/cos(teta), cos(phi)/cos(teta);
  Eigen::Vector3d euler_rate = H*odometry.angular_velocity_B;

  gController.lqr_final_U.X[9 ]  = euler_rate.x();
  gController.lqr_final_U.X[10]  = euler_rate.y();
  gController.lqr_final_U.X[11]  = euler_rate.z();
}

/*void MultiDofJointTrajectoryCallback(
    const trajectory_msgs::MultiDOFJointTrajectoryConstPtr& msg) {
    mav_msgs::EigenTrajectoryPoint eigen_reference;
    mav_msgs::eigenTrajectoryPointFromMsg(msg->points.front(), &eigen_reference);

    gController.lqr_final_U.z_ref    = eigen_reference.position_W.z();

    if (!gCommand_active){
      gCommand_active      = true;
      // gCommand_time        = ros::Time::now();
    }
}*/

void CommandPoseCallback(const geometry_msgs::PoseStampedConstPtr& pose_msg) {
  mav_msgs::EigenTrajectoryPoint eigen_reference;
  mav_msgs::eigenTrajectoryPointFromPoseMsg(*pose_msg, &eigen_reference);
  gController.lqr_final_U.x_ref    = eigen_reference.position_W.x();
  gController.lqr_final_U.y_ref    = eigen_reference.position_W.y();
  gController.lqr_final_U.z_ref    = eigen_reference.position_W.z();
  gController.lqr_final_U.psi_ref  = 0.0;
  if (!gCommand_active){
    gCommand_active      = true;
  }
}

void LostControlCallback(const gsft_control::LOEConstPtr& loe_msg) {
 for (int i = 0; i < 6; i++) {
    gLOE[i] = loe_msg->LOE[i];
  }
  std::cout << "[ INFO] [" << ros::Time::now() <<
    "]: ---------- TND LOE0 = " << gLOE[0] << std::endl;
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "matlab_lqr_firefly_node");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ROS_INFO("Matlab_lqr_firefly_node main started");

  ros::Subscriber odometry_sub_;
  odometry_sub_ = nh.subscribe(mav_msgs::default_topics::ODOMETRY, 1, OdometryCallback);

  ros::Subscriber cmd_pose_sub_;
  cmd_pose_sub_ = nh.subscribe(mav_msgs::default_topics::COMMAND_POSE, 1, CommandPoseCallback);

  /*ros::Subscriber cmd_multi_dof_joint_trajectory_sub;
  cmd_multi_dof_joint_trajectory_sub = nh.subscribe(mav_msgs::default_topics::COMMAND_TRAJECTORY, 1, MultiDofJointTrajectoryCallback);*/

  ros::Subscriber lost_control_sub_;
  lost_control_sub_ = nh.subscribe(gsft_control::default_topics::LOE, 1, LostControlCallback);

  ros::Publisher virtual_control_pub_;
  virtual_control_pub_ = nh.advertise<gsft_control::VirtualControl>(gsft_control::default_topics::VIRTUAL_CONTROL, 1);

  ros::Publisher motor_RPM_pub_;
  motor_RPM_pub_ = nh.advertise<mav_msgs::Actuators>(
        gsft_control::default_topics::MOTOR_RPM, 1);

  ros::Publisher motor_velocity_reference_pub_;
  motor_velocity_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
        mav_msgs::default_topics::COMMAND_ACTUATORS, 1);

  ros::Rate r(60);

  gCommand_active = false;
  for (unsigned int i=0; i< 6; i++) {
    gLOE[i] = 0.0;
  }
  gController.initialize();

  while(ros::ok()) {
    if (gCommand_active) {
        gController.step();
        Eigen::VectorXd motor_RPM(6);           // range 0 .. 10000 RPM
        Eigen::VectorXd motor_command(6);       // range 0 .. 200
        Eigen::VectorXd motor_normalized(6);    // range 0 .. 1
        Eigen::VectorXd motor_speed(6);         // range 0 .. 1047 rad/s

        for(unsigned int i=0; i< 6; i++) {
            motor_RPM[i]     = gController.lqr_final_Y.motor_RPM[i]*(1.0 - gLOE[i]);
            motor_command[i] = gController.lqr_final_Y.motor_command[i]*(1.0 - gLOE[i]);
            motor_speed[i]   = gController.lqr_final_Y.motor_speed[i]*(1.0 - gLOE[i]);
            motor_normalized[i] = motor_command[i]/200.0;
        }

        // Publish: RPM and command in 0 .. 200
        mav_msgs::ActuatorsPtr motorRPM_msg(new mav_msgs::Actuators);
        motorRPM_msg->angular_velocities.clear();
        motorRPM_msg->normalized.clear();
        for (int i = 0; i < 6; i++) {
          motorRPM_msg->angular_velocities.push_back(motor_RPM[i]);
          motorRPM_msg->normalized.push_back(motor_command[i]);
        }
        motorRPM_msg->header.stamp =  ros::Time::now();
        motor_RPM_pub_.publish(motorRPM_msg);

        // Publish: Rotor speed (rad/s) and normalized in 0 .. 1
        mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
        actuator_msg->angular_velocities.clear();
        actuator_msg->normalized.clear();
        for (int i = 0; i < 6; i++) {
          actuator_msg->angular_velocities.push_back(motor_speed[i]);
          actuator_msg->normalized.push_back(motor_normalized[i]);
        }
        actuator_msg->header.stamp =  ros::Time::now();
        motor_velocity_reference_pub_.publish(actuator_msg);

        // Publish: virtual control (thrust, moment x, moment y)
        gsft_control::VirtualControlPtr virtual_contrl_msg(new gsft_control::VirtualControl);
        virtual_contrl_msg->total_thrust = gController.lqr_final_Y.virtual_control[0];

        Eigen::VectorXd moment(3);
        for(unsigned int i=0; i< 2; i++)
            moment[i] = gController.lqr_final_Y.virtual_control[i+1];
        moment[2] = 0.0;    // yaw
        mav_msgs::vectorEigenToMsg(moment, &virtual_contrl_msg->moment);

        virtual_control_pub_.publish(virtual_contrl_msg);

    } else {
      // Publish: Rotor speed
      mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
      actuator_msg->angular_velocities.clear();

      for (int i = 0; i < 6; i++) {
        actuator_msg->angular_velocities.push_back(0.0);
        actuator_msg->normalized.push_back(0.0);
      }

      actuator_msg->header.stamp =  ros::Time::now();
      motor_velocity_reference_pub_.publish(actuator_msg);
    }
    ros::spinOnce();
    r.sleep();
  }
  gController.terminate();

  return 0;
}
