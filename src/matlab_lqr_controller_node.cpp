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

#include <gsft_control/VirtualControl.h>
#include <gsft_control/XYZYawError.h>
#include <lqr_firefly.h>

lqr_fireflyModelClass gController;

bool gCommand_active;
ros::Time gCommand_time;

void OdometryCallback(const nav_msgs::Odometry::ConstPtr &odom) {
  mav_msgs::EigenOdometry odometry;
  mav_msgs::eigenOdometryFromMsg(*odom, &odometry);

  gController.lqr_firefly_U.X[0 ]  = odometry.position_W.x();
  gController.lqr_firefly_U.X[1 ]  = odometry.position_W.y();
  gController.lqr_firefly_U.X[2 ]  = odometry.position_W.z();

  Eigen::Matrix3d R_W_B = odometry.orientation_W_B.toRotationMatrix();
  Eigen::Vector3d velocity_W =  R_W_B * odometry.velocity_B;

  gController.lqr_firefly_U.X[3 ]  = velocity_W.x();
  gController.lqr_firefly_U.X[4 ]  = velocity_W.y();
  gController.lqr_firefly_U.X[5 ]  = velocity_W.z();

  double psi, phi, teta;
  psi = atan2(R_W_B(1,0),R_W_B(0,0));
  phi = atan2(R_W_B(2,1),R_W_B(2,2));
  teta = asin(-R_W_B(2,0));

  gController.lqr_firefly_U.X[6 ]  = phi;
  gController.lqr_firefly_U.X[7 ]  = teta;
  gController.lqr_firefly_U.X[8 ]  = psi;

  Eigen::Matrix3d H;
  H << 1.0, sin(phi)*tan(teta), cos(phi)*tan(teta),
       0.0, cos(phi),           -sin(phi),
       0.0, sin(phi)/cos(teta), cos(phi)/cos(teta);
  Eigen::Vector3d euler_rate = H*odometry.angular_velocity_B;

  gController.lqr_firefly_U.X[9 ]  = euler_rate.x();
  gController.lqr_firefly_U.X[10]  = euler_rate.y();
  gController.lqr_firefly_U.X[11]  = euler_rate.z();
}

void MultiDofJointTrajectoryCallback(
    const trajectory_msgs::MultiDOFJointTrajectoryConstPtr& msg) {
    mav_msgs::EigenTrajectoryPoint eigen_reference;
    mav_msgs::eigenTrajectoryPointFromMsg(msg->points.front(), &eigen_reference);

    gController.lqr_firefly_U.x_ref    = eigen_reference.position_W.x();
    gController.lqr_firefly_U.y_ref    = eigen_reference.position_W.y();
    gController.lqr_firefly_U.z_ref    = eigen_reference.position_W.z();
    gController.lqr_firefly_U.psi_ref  = eigen_reference.getYaw();
    if (!gCommand_active){
      gCommand_active      = true;
      gCommand_time        = ros::Time::now();
    }
}

void CommandPoseCallback(
  const geometry_msgs::PoseStampedConstPtr& pose_msg) {
  mav_msgs::EigenTrajectoryPoint eigen_reference;
  mav_msgs::eigenTrajectoryPointFromPoseMsg(*pose_msg, &eigen_reference);
  gController.lqr_firefly_U.x_ref    = eigen_reference.position_W.x();
  gController.lqr_firefly_U.y_ref    = eigen_reference.position_W.y();
  gController.lqr_firefly_U.z_ref    = eigen_reference.position_W.z();
  gController.lqr_firefly_U.psi_ref  = eigen_reference.getYaw();
  if (!gCommand_active){
    gCommand_active      = true;
    gCommand_time        = ros::Time::now();
  }
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

  ros::Subscriber cmd_multi_dof_joint_trajectory_sub;
  cmd_multi_dof_joint_trajectory_sub = nh.subscribe(mav_msgs::default_topics::COMMAND_TRAJECTORY, 1, MultiDofJointTrajectoryCallback);

  ros::Publisher xyzyaw_error_pub_;
  xyzyaw_error_pub_ = nh.advertise<gsft_control::XYZYawError>(gsft_control::default_topics::XYZYAW_ERROR, 1);

  ros::Publisher virtual_control_pub_;
  virtual_control_pub_ = nh.advertise<gsft_control::VirtualControl>(gsft_control::default_topics::VIRTUAL_CONTROL, 1);

  ros::Publisher motor_velocity_reference_pub_;
  motor_velocity_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
        mav_msgs::default_topics::COMMAND_ACTUATORS, 1);

  ros::Rate r(60);

  gCommand_active = false;
  gController.initialize();

  while(ros::ok()) {
    if (gCommand_active) {
        gController.step();
        Eigen::VectorXd omega(6);
        Eigen::VectorXd omega_normalized(6);
        Eigen::VectorXd motor_RPM(6);
        Eigen::VectorXd motor_command(6);

        for(unsigned int i=0; i< 6; i++) {
            omega[i] = gController.lqr_firefly_Y.omega[i];             // max 10000 RPM ~ 1047 rad/s
            motor_RPM[i] = omega[i]*9.5493;                            // 1 rad/s = 9.5493 RPM
            motor_command[i] =  (motor_RPM[i] - 1250.0)/43.75;            // mapping, range 0 .. 200
            motor_command[i] = fmax(fmin(motor_command[i], 200.0),0.0);
            omega_normalized[i] = motor_command[i]/200.0;              // mapping, range 0 .. 1
        }
        // Publish: Rotor speed
        mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
        actuator_msg->angular_velocities.clear();

        for (int i = 0; i < 6; i++) {
          actuator_msg->angular_velocities.push_back(omega[i]);
          actuator_msg->normalized.push_back(omega_normalized[i]);
        }

        actuator_msg->header.stamp =  ros::Time::now();
        motor_velocity_reference_pub_.publish(actuator_msg);

        // Publish: error - RPY
        gsft_control::XYZYawErrorPtr xyzyaw_error_msg(new gsft_control::XYZYawError);
        Eigen::VectorXd position_error(3);
        //for(unsigned int i=0; i< 3; i++)
            // position_error[i] = gController.lqr_firefly_Y.error[i];
        position_error[0] = gController.lqr_firefly_U.X[6];  // roll
        position_error[1] = gController.lqr_firefly_U.X[7];  // pitch
        position_error[2] = gController.lqr_firefly_U.X[8];  // yaw
        mav_msgs::vectorEigenToMsg(position_error, &xyzyaw_error_msg->position_error);

        xyzyaw_error_msg->yaw_error = gController.lqr_firefly_Y.error[3];
        xyzyaw_error_pub_.publish(xyzyaw_error_msg);

        // Publish: virtual control - RPY rate
        gsft_control::VirtualControlPtr virtual_contrl_msg(new gsft_control::VirtualControl);
        Eigen::VectorXd moment(3);
        //for(unsigned int i=1; i< 4; i++)
        //    moment[i-1] = gController.lqr_firefly_Y.virtual_control[i];

        moment[0] = gController.lqr_firefly_U.X[9];  // roll rate
        moment[1] = gController.lqr_firefly_U.X[10];  // pitch rate
        moment[2] = gController.lqr_firefly_U.X[11];  // yaw rate

        mav_msgs::vectorEigenToMsg(moment, &virtual_contrl_msg->moment);

        virtual_contrl_msg->total_thrust = gController.lqr_firefly_Y.virtual_control[0];
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
