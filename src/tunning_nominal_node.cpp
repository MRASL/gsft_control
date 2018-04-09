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
#include <gsft_control/UAVState.h>
#include <tunning_nominal.h>

#include <dynamic_reconfigure/server.h>
#include <gsft_control/controllerDynConfig.h>

tunning_nominalModelClass gController;

bool gPublish;
bool gInit_flag;
bool gLanding_flag;
bool gEmergency_status;

int  gTest_mode;

Eigen::VectorXd gY0(4);        // initial position (equilibrium)
Eigen::VectorXd gRef(4);       // references (x, y, z, yaw)
Eigen::VectorXd gGain(18);
Eigen::VectorXd gLOE(6);
Eigen::VectorXd gLOE_t(6);

double gPsi;                   // heading (rad)

mav_msgs::EigenOdometry gOdometry;

void OdometryCallback(const nav_msgs::Odometry::ConstPtr &odom) {
  mav_msgs::eigenOdometryFromMsg(*odom, &gOdometry);
  if ((gOdometry.position_W.x() > 2.5)||(gOdometry.position_W.x() < -2.5)||(gOdometry.position_W.y() > 2.5)||(gOdometry.position_W.y() < -2.5)||(gOdometry.position_W.z() > 1.75))
  {
    if (!gEmergency_status){
      gEmergency_status = true;
    }
  }
  //if (gLanding_flag || gInit)
}

void controller_dyn_callback(gsft_control::controllerDynConfig &config, uint32_t level) {
  if (config.RESET) {
    // TO DO : reset parameters, gains
    config.RESET = false;
  }
  else if (level & gsft_control::controllerDyn_ENABLE_CTRL){
      gTest_mode = config.test_mode;
      if (config.enable_take_off && !gInit_flag){     // only once
        gY0[0]    = gOdometry.position_W.x();
        gY0[1]    = gOdometry.position_W.y();
        gY0[2]    = gOdometry.position_W.z();
        gY0[3]    = gPsi;
      //  if (config.test_mode == gsft_control::controllerDyn_TEST_MANUAL){
        gRef[0]   = gY0[0];
        gRef[1]   = gY0[1];
        gRef[2]   = config.ref_z;
        gRef[3]   = gY0[3];
      //  }

      /*  gGain[0]  = config.kx;      // x
        gGain[1]  = config.kvx;     // vx
        gGain[2]  = 0.0;            // integral x
        gGain[3]  = config.ky;      // y
        gGain[4]  = config.kvy;
        gGain[5]  = 0.0;
        gGain[6]  = config.kz;      // z
        gGain[7]  = config.kvz;
        gGain[8]  = config.kiz;
        gGain[9]  = config.kphi;    // roll
        gGain[10] = config.kp;
        gGain[11] = config.kiphi;
        gGain[12] = config.ktheta;  // pitch
        gGain[13] = config.kq;
        gGain[14] = config.kitheta;
        gGain[15] = config.kpsi;    // yaw
        gGain[16] = config.kr;
        gGain[17] = config.kipsi;  */
        config.kx      = gGain[0];
        config.kvx     = gGain[1];
        config.kix     = gGain[2];
        config.ky      = gGain[3] ;
        config.kvy     = gGain[4];
        config.kiy     = gGain[5];
        config.kz      = gGain[6];
        config.kvz     = gGain[7];
        config.kiz     = gGain[8];
        config.kphi    = gGain[9];
        config.kp      = gGain[10];
        config.kiphi   = gGain[11];
        config.ktheta  = gGain[12];
        config.kq      = gGain[13];
        config.kitheta =  gGain[14];
        config.kpsi    = gGain[15];
        config.kr      = gGain[16];
        config.kipsi   = gGain[17];

        gLOE[0]   = config.LOE_1;
        gLOE[1]   = config.LOE_2;
        gLOE[2]   = config.LOE_3;
        gLOE[3]   = config.LOE_4;
        gLOE[4]   = config.LOE_5;
        gLOE[5]   = config.LOE_6;
        gLOE_t[0]   = config.LOE_t1;
        gLOE_t[1]   = config.LOE_t2;
        gLOE_t[2]   = config.LOE_t3;
        gLOE_t[3]   = config.LOE_t4;
        gLOE_t[4]   = config.LOE_t5;
        gLOE_t[5]   = config.LOE_t6;

        gInit_flag = true;
        ROS_INFO("Take-off Request: %s with Test_mode = %d",config.enable_take_off?"True":"False",gTest_mode);

        config.enable_take_off = false;

      }
      else if (config.enable_landing && !gLanding_flag){   // only once
        gRef[0]  = gOdometry.position_W.x();
        gRef[1]  = gOdometry.position_W.y();
        gRef[2]  = 0.0;
        gRef[3]  = gPsi;
        gTest_mode = gsft_control::controllerDyn_TEST_MANUAL;
        gLanding_flag = true;
        ROS_INFO("Landing Request: %s at x_ref = %f, y_ref = %f,psi_ref = %f(deg)",config.enable_landing?"True":"False",gRef[0],gRef[1],gRef[3]*180.0/3.14159);
        config.enable_landing  = false;
      }
      else if (gTest_mode == gsft_control::controllerDyn_TEST_MANUAL){
        if (config.send_waypoint){
          gRef[0]   = config.ref_x;
          gRef[1]   = config.ref_y;
          gRef[2]   = config.ref_z;
          gRef[3]   = config.ref_yaw_deg*3.14159/180.0;
          ROS_INFO("Waypoint Request: x_ref = %f, y_ref = %f, z_ref = %f, psi_ref = %f(deg)",gRef[0],gRef[1],gRef[2],gRef[3]);
          config.send_waypoint   = false;
        }
        else if (config.new_controller_gains){
          gGain[0]  = config.kx;
          gGain[1]  = config.kvx;
          gGain[2]  = config.kix;

          gGain[3]  = config.ky;
          gGain[4]  = config.kvy;
          gGain[5]  = config.kiy;

          gGain[6]  = config.kz;
          gGain[7]  = config.kvz;
          gGain[8]  = config.kiz;

          gGain[9]  = config.kphi;
          gGain[10] = config.kp;
          gGain[11] = config.kiphi;

          gGain[12] = config.ktheta;
          gGain[13] = config.kq;
          gGain[14] = config.kitheta;

          gGain[15] = config.kpsi;
          gGain[16] = config.kr;
          gGain[17] = config.kipsi;
          ROS_INFO("New controller gains");
          config.new_controller_gains   = false;
        }
      }
  }
}

/*void LostControlCallback(const gsft_control::LOEConstPtr& loe_msg) {
 for (int i = 0; i < 6; i++) {
    gLOE[i] = loe_msg->LOE[i];
  }
  std::cout << "[ INFO] [" << ros::Time::now() <<
    "]: ---------- TND LOE0 = " << gLOE[0] << std::endl;
}*/

void timmerCallback(const ros::TimerEvent&)
{
  if (!gPublish){
    gPublish = true;
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "tunning_nominal_node");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ROS_INFO("tunning_nominal_node main started");

  ros::Subscriber odometry_sub_;
  odometry_sub_ = nh.subscribe(mav_msgs::default_topics::ODOMETRY, 1, OdometryCallback);

  /*ros::Subscriber lost_control_sub_;
  lost_control_sub_ = nh.subscribe(gsft_control::default_topics::LOE, 1, LostControlCallback);*/

  ros::Publisher motor_RPM_reference_pub_;          // motor speed RPM   => Asctec Firefly test
  motor_RPM_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
        gsft_control::default_topics::COMMAND_RPM, 1);

  ros::Publisher motor_velocity_reference_pub_;     // motor speed rad/s => Gazebo test
  motor_velocity_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
        mav_msgs::default_topics::COMMAND_ACTUATORS, 1);

  ros::Publisher uav_state_pub_;
  uav_state_pub_ = nh.advertise<gsft_control::UAVState>(gsft_control::default_topics::UAV_STATE, 1);

  ros::Timer timer = nh.createTimer(ros::Duration(0.01),timmerCallback);

  ros::Rate r(1000);

  gInit_flag        = false;
  gLanding_flag     = false;
  gEmergency_status = false;
  gPublish          = false;

  gRef  << 0.0, 0.0, 0.0, 0.0;
  gGain = Eigen::VectorXd::Zero(18);
  gLOE  = Eigen::VectorXd::Zero(6);
  gLOE_t  = Eigen::VectorXd::Zero(6);
  gY0   << 0.0, 0.0, 0.0, 0.0;

  dynamic_reconfigure::Server<gsft_control::controllerDynConfig> server;
  dynamic_reconfigure::Server<gsft_control::controllerDynConfig>::CallbackType f;
  f = boost::bind(&controller_dyn_callback, _1, _2);
  server.setCallback(f);

  double phi, theta;
  Eigen::Matrix3d R_W_B;
  Eigen::Vector3d velocity_W ;

  Eigen::VectorXd motor_RPM(6);           // range 0 .. 10000 RPM
  Eigen::VectorXd motor_command(6);       // range 0 .. 200
  Eigen::VectorXd motor_speed(6);         // range 0 .. 1047 rad/s

  bool control_actived = false;
  bool end_mission  = false;

  gGain[0]  = 0.1019;       // x
  gGain[1]  = 0.1529;        // vx
  gGain[2]  = 0.0255;      // integral x
  gGain[3]  = -0.1019;      // y
  gGain[4]  = -0.1529;
  gGain[5]  = -0.0255;
  gGain[6]  = 13.86;      // z
  gGain[7]  = 6.93;
  gGain[8]  = 10.395;
  gGain[9]  = 1.2512;     // roll
  gGain[10] = 0.3128;
  gGain[11] = 1.8768;
  gGain[12] = 1.6521;     // pitch
  gGain[13] = 0.4130;
  gGain[14] = 2.4782;
  gGain[15] = 0.2198;     // yaw
  gGain[16] = 0.2198;
  gGain[17] = 0.0824;

  while(ros::ok()) {
    R_W_B = gOdometry.orientation_W_B.toRotationMatrix();
    velocity_W =  R_W_B * gOdometry.velocity_B;

    gPsi = atan2(R_W_B(1,0),R_W_B(0,0));
    phi  = atan2(R_W_B(2,1),R_W_B(2,2));
    theta = asin(-R_W_B(2,0));

    if (gInit_flag && !control_actived) {                     // only once when controller is not actived
        gController.initialize();
        control_actived = true;

        for (unsigned int i=0; i< 6; i++) {
          gController.tunning_nominal_U.LOE_a[i]  = gLOE[i];     // fault amplitude
        }
        for (unsigned int i=0; i< 6; i++) {
          gController.tunning_nominal_U.LOE_t[i]  = gLOE_t[i];   // fault time
        }
        for (unsigned int i=0; i< 18; i++) {
          ROS_INFO("Controller gain k[%d] = %f",i,gGain[i]);
        }
    }

    if (control_actived) {                                    // controller active after take-off request
        gController.tunning_nominal_U.mode = gTest_mode;

        for (unsigned int i=0; i< 4; i++) {
          gController.tunning_nominal_U.ref[i]  = gRef[i];
        }
        for (unsigned int i=0; i< 4; i++) {
          gController.tunning_nominal_U.Y0[i]   = gY0[i];
        }
        for (unsigned int i=0; i< 18; i++) {
          gController.tunning_nominal_U.gain[i] = gGain[i];
        }
        gController.tunning_nominal_U.X[0]  = gOdometry.position_W.x();
        gController.tunning_nominal_U.X[1]  = gOdometry.position_W.y();
        gController.tunning_nominal_U.X[2]  = gOdometry.position_W.z();
        gController.tunning_nominal_U.X[3 ]  = velocity_W.x();
        gController.tunning_nominal_U.X[4 ]  = velocity_W.y();
        gController.tunning_nominal_U.X[5 ]  = velocity_W.z();
        gController.tunning_nominal_U.X[6 ]  = phi;
        gController.tunning_nominal_U.X[7 ]  = theta;
        gController.tunning_nominal_U.X[8 ]  = gPsi;
        gController.tunning_nominal_U.X[9 ]  = gOdometry.angular_velocity_B.x();
        gController.tunning_nominal_U.X[10]  = gOdometry.angular_velocity_B.y();
        gController.tunning_nominal_U.X[11]  = gOdometry.angular_velocity_B.z();

        // Run Matlab controller
        gController.step();

        // Received data from Matlab
        for(unsigned int i=0; i< 6; i++) {
            if (gEmergency_status || (gLanding_flag && (gOdometry.position_W.z() <= 0.175)))
            {
              motor_command[i] = 1.0;
              motor_RPM[i]     = 1250;
              motor_speed[i]   = 130.0;
            }
            else
            {
              motor_command[i] = gController.tunning_nominal_Y.motor_command[i];        // normalized [1 .. 200] => Asctec Firefly
              motor_RPM[i]     = 1250.0 + motor_command[i]*43.75;                   // real RPM
              motor_speed[i]   = motor_RPM[i]/9.5493;                               // rad/s => Gazebo
            }
        }

        // Send command: RPM and normalized command in 0 .. 200
        mav_msgs::ActuatorsPtr motorRPM_msg(new mav_msgs::Actuators);
        motorRPM_msg->angular_velocities.clear();
        motorRPM_msg->normalized.clear();
        for (int i = 0; i < 6; i++) {
          motorRPM_msg->angular_velocities.push_back(motor_RPM[i]);
          motorRPM_msg->normalized.push_back(motor_command[i]);
        }
        motorRPM_msg->header.stamp =  ros::Time::now();
        motor_RPM_reference_pub_.publish(motorRPM_msg);

        // Send command: Rotor speed (rad/s)
        mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
        actuator_msg->angular_velocities.clear();
        actuator_msg->normalized.clear();
        for (int i = 0; i < 6; i++) {
          actuator_msg->angular_velocities.push_back(motor_speed[i]);
        }
        actuator_msg->header.stamp =  ros::Time::now();
        motor_velocity_reference_pub_.publish(actuator_msg);

    } else { // control_actived = false ( before take-off)
      mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
      actuator_msg->angular_velocities.clear();

      for (int i = 0; i < 6; i++) {
        actuator_msg->angular_velocities.push_back(0.0);
        actuator_msg->normalized.push_back(0.0);
      }
      actuator_msg->header.stamp =  ros::Time::now();
      motor_RPM_reference_pub_.publish(actuator_msg);
      motor_velocity_reference_pub_.publish(actuator_msg);
    }

    if (gEmergency_status)
    {
      ROS_ERROR("tunning_nominal_node emergency status");
      ROS_INFO("x = %f, y = %f, z = %f",gOdometry.position_W.x(),gOdometry.position_W.y(),gOdometry.position_W.z());
      ros::Duration(0.5).sleep();
      gController.terminate();
      break;
    }

    if (gLanding_flag && (gOdometry.position_W.z() <= 0.175))
    {
      ROS_INFO("Controller desactivated");
      ROS_INFO("x = %f, y = %f, z = %f",gOdometry.position_W.x(),gOdometry.position_W.y(),gOdometry.position_W.z());
      ros::Duration(0.5).sleep();
      gController.terminate();
      break;
    }

    // Publish data: UAV state in World frame
    if (gPublish){
      gsft_control::UAVStatePtr uav_state_msg(new gsft_control::UAVState);
      uav_state_msg->position_ref.x  = gController.tunning_nominal_Y.ref_out[0];    // gRef only for manual test
      uav_state_msg->position_ref.y  = gController.tunning_nominal_Y.ref_out[1];
      uav_state_msg->position_ref.z  = gController.tunning_nominal_Y.ref_out[2];
      uav_state_msg->heading_ref     = gController.tunning_nominal_Y.ref_out[3];

      uav_state_msg->position_W.x  = gOdometry.position_W.x();
      uav_state_msg->position_W.y  = gOdometry.position_W.y();
      uav_state_msg->position_W.z  = gOdometry.position_W.z();
      uav_state_msg->velocity_B.x  = velocity_W.x();
      uav_state_msg->velocity_B.y  = velocity_W.y();
      uav_state_msg->velocity_B.z  = velocity_W.z();
      uav_state_msg->euler_angle.x = phi;
      uav_state_msg->euler_angle.y = theta;
      uav_state_msg->euler_angle.z = gPsi;
      uav_state_msg->rotation_speed_B.x  = gOdometry.angular_velocity_B.x();
      uav_state_msg->rotation_speed_B.y  = gOdometry.angular_velocity_B.y();
      uav_state_msg->rotation_speed_B.z  = gOdometry.angular_velocity_B.z();
      uav_state_msg->total_thrust  = gController.tunning_nominal_Y.virtual_control[0];
      uav_state_msg->moment.x      = gController.tunning_nominal_Y.virtual_control[1];
      uav_state_msg->moment.y      = gController.tunning_nominal_Y.virtual_control[2];
      uav_state_msg->moment.z      = gController.tunning_nominal_Y.virtual_control[3];

      uav_state_msg->LOE13.x  = gController.tunning_nominal_Y.LOE[0];
      uav_state_msg->LOE13.y  = gController.tunning_nominal_Y.LOE[1];
      uav_state_msg->LOE13.z  = gController.tunning_nominal_Y.LOE[2];

      uav_state_msg->header.stamp  =  ros::Time::now();
      uav_state_pub_.publish(uav_state_msg);
      gPublish = false;
    }

    ros::spinOnce();
    r.sleep();
  } // end while

  return 0;
}
