#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

#include <tf/tf.h>
#include <tf_conversions/tf_eigen.h>
//#include <trajectory_msgs/MultiDOFJointTrajectory.h>
// #include <mav_msgs/eigen_mav_msgs.h>

#include "parameters.h"
#include "parameters_ros.h"
#include "common.h"

#include <tuning_GS1.h>
#include <dynamic_reconfigure/server.h>

#include <gsft_control/LOE.h>
#include <gsft_control/UAVState.h>
#include <gsft_control/controllerGS1DynConfig.h>

tuning_GS1ModelClass gController;

bool gFirst_odom;
bool gPublish;
bool gInit_flag;
bool gLanding_flag;
bool gEmergency_status;
int  gTest_mode;
int  gLOE_mode;
double gPsi;                    // heading (rad)

Eigen::VectorXd gY0(4);         // initial position (equilibrium)
Eigen::VectorXd gRef(4);        // references (x, y, z, yaw)
Eigen::VectorXd gGain(19);
Eigen::VectorXd gLOE(6);        // LOE trued
Eigen::VectorXd gLOE_t(6);      // LOE moment
Eigen::VectorXd gThrust_measure(6);

gsft_control::EigenOdometry gOdometry;

void controller_dyn_callback(gsft_control::controllerGS1DynConfig &config, uint32_t level) {  // callback if there is a change in dyn_reconfigure
  if (config.RESET) {
    // TO DO : reset parameters, gains
    config.RESET = false;
  }
  else if (level & gsft_control::controllerGS1Dyn_ENABLE_CTRL){
      if (config.new_controller_gains){
        gGain[0]  = config.kx;      // x
        gGain[1]  = config.kvx;     // vx
        gGain[2]  = config.kix;     // integral x
        gGain[3]  = config.ky;      // y
        gGain[4]  = config.kvy;
        gGain[5]  = config.kiy;
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
        gGain[17] = config.kipsi;

        ROS_INFO("New controller gains");
        config.new_controller_gains   = false;
      }

      // Note: dynamic reconfigure is called when created by server_dyn.setCallback(f_dyn)
      //               i.e. before the first Odometry available
      // Compare mode: because config.enable_take_off always TRUE
      //               => need gFirst_odom condition: do not get initial value of gOdometry (all 0)
      //               => need recall this function after first odom available to get correct initial point, then take-off
      // Experimental test: initial point before take off command, not after first odom
      if (config.enable_take_off && !gInit_flag && gFirst_odom){     // only once
        gY0[0]    = gOdometry.position.x();           // Initial point
        gY0[1]    = gOdometry.position.y();
        gY0[2]    = gOdometry.position.z();
        gY0[3]    = gPsi;
      //  if (config.test_mode == gsft_control::controllerGS1Dyn_TEST_MANUAL){
        gRef[0]   = gY0[0];
        gRef[1]   = gY0[1];
        gRef[2]   = config.ref_z;
        gRef[3]   = gY0[3];
      //  }
        gGain[0]  = config.kx;      // x
        gGain[1]  = config.kvx;     // vx
        gGain[2]  = config.kix;     // integral x
        gGain[3]  = config.ky;      // y
        gGain[4]  = config.kvy;
        gGain[5]  = config.kiy;
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
        gGain[17] = config.kipsi;

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

        gTest_mode = config.test_mode;
        gLOE_mode  = config.LOE_mode;

        gInit_flag = true;
        ROS_INFO("Test_mode = %d, LOE_mode = %d",gTest_mode,gLOE_mode);
        ROS_INFO("Take-off Request: %s at x_ref = %f, y_ref = %f, z_ref = %f, psi_ref = %f(deg)",config.enable_take_off?"True":"False",gRef[0],gRef[1],gRef[2],gRef[3]*180.0/gsft_control::kDefaultPi);

        config.enable_take_off = false;

      }
      else if (config.enable_landing && !gLanding_flag){   // only once
        gRef[0]  = gOdometry.position.x();
        gRef[1]  = gOdometry.position.y();
        gRef[2]  = gY0[2];
        gRef[3]  = gPsi;
        gTest_mode = gsft_control::controllerGS1Dyn_TEST_MANUAL;
        gLanding_flag = true;
        ROS_INFO("Landing Request: %s at x_ref = %f, y_ref = %f, z_ref = %f, psi_ref = %f(deg)",config.enable_landing?"True":"False",gRef[0],gRef[1],gRef[2],gRef[3]*180.0/gsft_control::kDefaultPi);
        config.enable_landing  = false;
      }
      else if (gTest_mode == gsft_control::controllerGS1Dyn_TEST_MANUAL){
        if (config.send_waypoint){
          gRef[0]   = config.ref_x;
          gRef[1]   = config.ref_y;
          gRef[2]   = config.ref_z;
          gRef[3]   = config.ref_yaw_deg*gsft_control::kDefaultPi/180.0;
          ROS_INFO("Waypoint Request: x_ref = %f, y_ref = %f, z_ref = %f, psi_ref = %f(deg)",gRef[0],gRef[1],gRef[2],gRef[3]*180.0/gsft_control::kDefaultPi);
          config.send_waypoint   = false;
        }
      }
  }
}

//ros::Time gPrev_it;
// Eigen::VectorXd gAng_acc_calcul(3); // derivative of angular velocity
void OdometryCallback(const nav_msgs::OdometryConstPtr& odom_msg) {
  gsft_control::eigenOdometryFromMsg(odom_msg, &gOdometry);   // new measurement

// Derivative of angular velocity => Angular acceleration
/*  ros::Time current_time = ros::Time::now();
  ros::Duration Td = current_time - gPrev_it;
  gPrev_it = current_time;
  Eigen::VectorXd prev_ang_velocity(3);
  prev_ang_velocity[0] = gOdometry.angular_velocity.x();  // old measurement
  mav_msgs::eigenOdometryFromMsg(*odom, &gOdometry);      // new measurement
  gAng_acc_calcul[0] = (gOdometry.angular_velocity.x() - prev_ang_velocity[0])/Td.toSec();
*/

  if ((gOdometry.position.x() > gsft_control::kDefaultXmax)||(gOdometry.position.x() < -gsft_control::kDefaultXmax)
    ||(gOdometry.position.y() > gsft_control::kDefaultYmax)||(gOdometry.position.y() < -gsft_control::kDefaultYmax)
    ||(gOdometry.position.z() > gsft_control::kDefaultZmax))
  {
    if (!gEmergency_status){
      gEmergency_status = true;
    }
  }
  if (!gFirst_odom){
    ROS_INFO("First odometry: x = %f, y = %f, z = %f",gOdometry.position.x(),gOdometry.position.y(),gOdometry.position.z());
    gFirst_odom = true;}
}

/*void LostControlCallback(const gsft_control::LOEConstPtr& loe_msg) {
 for (int i = 0; i < 6; i++) {
    gLOE[i] = loe_msg->LOE[i];
  }
  std::cout << "[ INFO] [" << ros::Time::now() <<
    "]: ---------- TND LOE0 = " << gLOE[0] << std::endl;
}*/

// ASCTEC test: command 0..200
void MotorSpeedCallback(const asctec_hl_comm::MotorSpeedConstPtr& motor_msg) {
  gsft_control::motorMsg2Thrust(motor_msg,&gThrust_measure);
  //ROS_INFO("Thrust T1 = %f(N)",gThrust_measure[0]);
}

// Gazebo: command rad/sec
void MotorSpeedGazeboCallback(const mav_msgs::ActuatorsConstPtr& motor_msg) {
  gsft_control::speedMsg2Thrust(motor_msg,&gThrust_measure);
// ROS_INFO("Thrust T1 = %f(N)",gThrust_measure[0]);
 // new measurement
}

void timerPublishCallback(const ros::TimerEvent&)
{
  if (!gPublish){
    gPublish = true;
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "tuning_GS1_node");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ROS_INFO("tuning_GS1_node main started");

  std::string test_scenario;  // Gazebo or Experimental test with Asctec Firefly
  pnh.getParam("scenario",test_scenario);
  ROS_INFO_STREAM("test scenario = " <<test_scenario);

  /*std::string frame_id;
  pnh.param("frame_id", frame_id, std::string("matlab")); */

  ros::Subscriber odometry_sub_;
  odometry_sub_ = nh.subscribe(gsft_control::kDefaultOdometryTopic, 1, OdometryCallback);

  ros::Subscriber motor_speed_sub_;
  if (test_scenario=="experimental"){
      motor_speed_sub_ = nh.subscribe(gsft_control::kDefaultMotorSpeedTopic, 1, MotorSpeedCallback);
  }
  else{       // Rotors simulator (Gazebo)
      motor_speed_sub_ = nh.subscribe(gsft_control::kDefaultMotorSpeedTopic, 1, MotorSpeedGazeboCallback);
  }
 /*ros::Subscriber lost_control_sub_;
  lost_control_sub_ = nh.subscribe(gsft_control::default_topics::LOE, 1, LostControlCallback);*/

  ros::Publisher motor_speed_reference_pub_;
  motor_speed_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
        gsft_control::kDefaultCommandMotorSpeedTopic, 1);   // 'command/motor_speed'

  ros::Publisher uav_state_pub_;
  uav_state_pub_ = nh.advertise<gsft_control::UAVState>(gsft_control::default_topics::UAV_STATE, 1);

  ros::Publisher LOE_pub_;
  LOE_pub_ = nh.advertise<gsft_control::LOE>(gsft_control::default_topics::LOE, 1);

  ros::Timer timerPublish = nh.createTimer(ros::Duration(0.01),timerPublishCallback);

  ros::Rate r(1000);

  gFirst_odom        = false;
  gPublish           = false;
  gInit_flag         = false;
  gLanding_flag      = false;
  gEmergency_status  = false;
  gTest_mode         = 0;
  gLOE_mode          = 1;   // nominal
  gPsi               = 0.0;

  gY0    << 0.0, 0.0, 0.0, 0.0;
  gRef   << 0.0, 0.0, 0.0, 0.0;
  gGain   = Eigen::VectorXd::Zero(19);
  gLOE    = Eigen::VectorXd::Zero(6);
  gLOE_t  = Eigen::VectorXd::Zero(6);
  gThrust_measure = Eigen::VectorXd::Zero(6);

  dynamic_reconfigure::Server<gsft_control::controllerGS1DynConfig> server_dyn;
  dynamic_reconfigure::Server<gsft_control::controllerGS1DynConfig>::CallbackType f_dyn;
  f_dyn = boost::bind(&controller_dyn_callback, _1, _2);
  server_dyn.setCallback(f_dyn);

  Eigen::Vector3d velocity_W ;
  Eigen::Vector3d euler_angles;

  Eigen::VectorXd motor_RPM(6);           // range 0 .. 10000 RPM
  Eigen::VectorXd motor_command(6);       // range 0 .. 200
  Eigen::VectorXd motor_speed(6);         // range 0 .. 1047 rad/s

  Eigen::VectorXd thrust_prev_sent(6);
  thrust_prev_sent    = Eigen::VectorXd::Zero(6);

  double temp_LOE_calcul = 0.0;
  bool controller_active = false;
  //  gPrev_it = ros::Time::now();

  static int seq = 0;
  while(ros::ok()) {
    /* https://github.com/libigl/eigen/blob/master/Eigen/src/Geometry/Quaternion.h
    Eigen::Matrix3d R_W_B = gOdometry.orientation.toRotationMatrix(); % Ned to body (not Euler matrix), ZYX order
    velocity_W =  R_W_B * gOdometry.velocity;
    double psi = atan2(R_W_B(1,0),R_W_B(0,0));
    double phi  = atan2(R_W_B(2,1),R_W_B(2,2));
    double theta = asin(-R_W_B(2,0));*/

    velocity_W = gOdometry.getVelocityWorld();

    gOdometry.getEulerAngles(&euler_angles);      // getEulerAnglesFromQuaternion: http://docs.ros.org/jade/api/mav_msgs/html/common_8h_source.html
    gPsi = euler_angles[2];
    // gPsi = gOdometry.getYaw();                 // result

    if (test_scenario == "compare" && gFirst_odom && !controller_active){
      server_dyn.setCallback(f_dyn);             // get initial point when first odom available, then take
      test_scenario = " ";
    }

    if (gInit_flag && !controller_active) {      // only once when controller is not actived
        gController.initialize();
        controller_active = true;

        for (unsigned int i=0; i< 6; i++) {
          gController.tuning_GS1_U.LOE_a[i]  = gLOE[i];     // fault amplitude
        }
        for (unsigned int i=0; i< 6; i++) {
          gController.tuning_GS1_U.LOE_t[i]  = gLOE_t[i];   // fault time
        }
        /*for (unsigned int i=0; i< 19; i++) {
          ROS_INFO("Controller gain k[%d] = %f",i,gGain[i]);
        }*/
    }

    if (controller_active) {                                // controller active after take-off request
        // Initialization before gController.step();
        gController.tuning_GS1_U.mode     = gTest_mode;     // 0 = manual, ...
        gController.tuning_GS1_U.LOE_mode = gLOE_mode;      // 1 = nominal, 2 = LOE true, ...

        for (unsigned int i=0; i< 4; i++) {
          gController.tuning_GS1_U.ref[i]  = gRef[i];
        }
        for (unsigned int i=0; i< 4; i++) {
          gController.tuning_GS1_U.Y0[i]   = gY0[i];
        }
        for (unsigned int i=0; i< 19; i++) {
          gController.tuning_GS1_U.gain[i] = gGain[i];
        }
        gController.tuning_GS1_U.X[0]   = gOdometry.position.x();
        gController.tuning_GS1_U.X[1]   = gOdometry.position.y();
        gController.tuning_GS1_U.X[2]   = gOdometry.position.z();
        gController.tuning_GS1_U.X[3 ]  = velocity_W.x();
        gController.tuning_GS1_U.X[4 ]  = velocity_W.y();
        gController.tuning_GS1_U.X[5 ]  = velocity_W.z();
        gController.tuning_GS1_U.X[6 ]  = euler_angles[0];
        gController.tuning_GS1_U.X[7 ]  = euler_angles[1];
        gController.tuning_GS1_U.X[8 ]  = gPsi;
        gController.tuning_GS1_U.X[9 ]  = gOdometry.angular_velocity.x();
        gController.tuning_GS1_U.X[10]  = gOdometry.angular_velocity.y();
        gController.tuning_GS1_U.X[11]  = gOdometry.angular_velocity.z();

        // Run Matlab controller
        gController.step();

        // Received data from Matlab
        for(unsigned int i=0; i< 6; i++) {
            if (gEmergency_status || (gLanding_flag && (gOdometry.position.z() <= gsft_control::kDefaultCutoffAltitude)))
            {
              motor_command[i] = 1.0;
              motor_RPM[i]     = 1250;
              motor_speed[i]   = 130.0;     // 1250/9.5493
            }
            else
            {
              motor_command[i] = gController.tuning_GS1_Y.motor_command[i];        // normalized [1 .. 200] => Asctec Firefly
              motor_RPM[i]     = 1250.0 + motor_command[i]*43.75;                  // real RPM
              motor_speed[i]   = motor_RPM[i]/9.5493;                              // rad/s => Gazebo
            }
        }

        // Send command: rad/s (Gazebo) and normalized command in 0 .. 200 (Asctec Firefly)
        mav_msgs::ActuatorsPtr motor_msg(new mav_msgs::Actuators);
        motor_msg->angular_velocities.clear();
        motor_msg->normalized.clear();
        for (int i = 0; i < 6; i++) {
          motor_msg->angular_velocities.push_back(motor_speed[i]);
          motor_msg->normalized.push_back(motor_command[i]);
        }
        motor_msg->header.stamp =  ros::Time::now();
        motor_speed_reference_pub_.publish(motor_msg);

        if (gController.tuning_GS1_Y.ref_out[2] <= 0.25 && gTest_mode > 0){  // landing (automatic trajectory)
          gLanding_flag = true;
        }

    } else { // controller_active = false ( before take-off)
      mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
      actuator_msg->angular_velocities.clear();

      for (int i = 0; i < 6; i++) {
        actuator_msg->angular_velocities.push_back(0.0);
        actuator_msg->normalized.push_back(0.0);
      }
      actuator_msg->header.stamp =  ros::Time::now();
      motor_speed_reference_pub_.publish(actuator_msg);
    }

    if (gEmergency_status)
    {
      ROS_ERROR("tuning_GS1_node emergency status");
      ROS_INFO("x = %f, y = %f, z = %f",gOdometry.position.x(),gOdometry.position.y(),gOdometry.position.z());
      ros::Duration(0.25).sleep();
      gController.terminate();
      break;
    }

    if (gLanding_flag && (gOdometry.position.z() <= gsft_control::kDefaultCutoffAltitude))
    {
      ROS_INFO("Controller desactivated");
      ROS_INFO("x = %f, y = %f, z = %f",gOdometry.position.x(),gOdometry.position.y(),gOdometry.position.z());
      ros::Duration(0.5).sleep();
      gController.terminate();
      break;
    }

    // Publish data: UAV state in World frame
    if (gPublish){
      gsft_control::UAVStatePtr uav_state_msg(new gsft_control::UAVState);
      uav_state_msg->position_ref.x  = gController.tuning_GS1_Y.ref_out[0];    // gRef only for manual test
      uav_state_msg->position_ref.y  = gController.tuning_GS1_Y.ref_out[1];
      uav_state_msg->position_ref.z  = gController.tuning_GS1_Y.ref_out[2];
      uav_state_msg->heading_ref     = gController.tuning_GS1_Y.ref_out[3];

      uav_state_msg->position_W.x   = gOdometry.position.x();
      uav_state_msg->position_W.y   = gOdometry.position.y();
      uav_state_msg->position_W.z   = gOdometry.position.z();
      uav_state_msg->velocity_W.x   = velocity_W.x();
      uav_state_msg->velocity_W.y   = velocity_W.y();
      uav_state_msg->velocity_W.z   = velocity_W.z();
      uav_state_msg->euler_angles.x = euler_angles[0];
      uav_state_msg->euler_angles.y = euler_angles[1];
      uav_state_msg->euler_angles.z = gPsi;
      uav_state_msg->rotation_speed_B.x  = gOdometry.angular_velocity.x();
      uav_state_msg->rotation_speed_B.y  = gOdometry.angular_velocity.y();
      uav_state_msg->rotation_speed_B.z  = gOdometry.angular_velocity.z();

    //  uav_state_msg->total_thrust  = gController.tuning_GS1_Y.virtual_control[0];
    //  uav_state_msg->moment.x      = gController.tuning_GS1_Y.virtual_control[1];
    //  uav_state_msg->moment.y      = gController.tuning_GS1_Y.virtual_control[2];
    //  uav_state_msg->moment.z      = gController.tuning_GS1_Y.virtual_control[3];

      uav_state_msg->thrust_pre.x    = gController.tuning_GS1_Y.thrust_pre[0];
      uav_state_msg->thrust_pre.y    = gController.tuning_GS1_Y.thrust_pre[1];
      uav_state_msg->thrust_pre.z    = gController.tuning_GS1_Y.thrust_pre[2];

      uav_state_msg->thrust_after.x  = gController.tuning_GS1_Y.thrust_after[0];
      uav_state_msg->thrust_after.y  = gController.tuning_GS1_Y.thrust_after[1];
      uav_state_msg->thrust_after.z  = gController.tuning_GS1_Y.thrust_after[2];

      uav_state_msg->vel_Kalman.x = gController.tuning_GS1_Y.vel_Kalman[0];
      uav_state_msg->vel_Kalman.y = gController.tuning_GS1_Y.vel_Kalman[1];
      uav_state_msg->vel_Kalman.z = gController.tuning_GS1_Y.vel_Kalman[2];

      uav_state_msg->acc_Kalman.x = gController.tuning_GS1_Y.acc_Kalman[0];
      uav_state_msg->acc_Kalman.y = gController.tuning_GS1_Y.acc_Kalman[1];
      uav_state_msg->acc_Kalman.z = gController.tuning_GS1_Y.acc_Kalman[2];

      uav_state_msg->M_Kalman.x = gController.tuning_GS1_Y.M_Kalman[0];
      uav_state_msg->M_Kalman.y = gController.tuning_GS1_Y.M_Kalman[1];
      uav_state_msg->M_Kalman.z = gController.tuning_GS1_Y.M_Kalman[2];

      uav_state_msg->Kxyz.x = gController.tuning_GS1_Y.gain_GS[6];
      uav_state_msg->Kxyz.y = gController.tuning_GS1_Y.gain_GS[9];
      uav_state_msg->Kxyz.z = gController.tuning_GS1_Y.gain_GS[0];
      uav_state_msg->Kpsi   = gController.tuning_GS1_Y.gain_GS[3];

      uav_state_msg->header.stamp  =  ros::Time::now();
      uav_state_pub_.publish(uav_state_msg);

      // LOE message
      if (controller_active){
        gsft_control::LOEPtr LOE_msg(new gsft_control::LOE);
        for(unsigned int i=0; i< 6; i++) {
          LOE_msg->LOE_true[i]   = gController.tuning_GS1_Y.LOE_true[i];
          if (i<3){
            LOE_msg->LOE_FDD[i]  = gController.tuning_GS1_Y.LOE13_estimated[i];
          }
          if (thrust_prev_sent[i]!=0){
              temp_LOE_calcul = 1-gThrust_measure[i]/thrust_prev_sent[i];
              LOE_msg->LOE_calcul[i] = temp_LOE_calcul;
             if (seq>10){
            //  gController.tuning_GS1_U.LOE_calcul[i] = fmin(fmax(temp_LOE_calcul,0.0),1.0);
               gController.tuning_GS1_U.LOE_calcul[i] = temp_LOE_calcul; 
             } else{
               gController.tuning_GS1_U.LOE_calcul[i] = 0.0;
             }
          }
          thrust_prev_sent[i] = gController.tuning_GS1_Y.thrust_pre[i];
        }
        if (seq>5){      // cheat
          LOE_msg->header.seq = seq;
          //LOE_msg->header.frame_id = frame_id;
          LOE_msg->header.stamp  =  ros::Time::now();
          LOE_pub_.publish(LOE_msg);
        }
        seq++;
      }
      gPublish = false;
    }

    ros::spinOnce();
    r.sleep();
  } // end while

  return 0;
}
