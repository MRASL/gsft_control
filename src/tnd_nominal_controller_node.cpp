#include <ros/ros.h>
#include <mav_msgs/default_topics.h>

#include "tnd_nominal_controller_node.h"

#include "rotors_control/parameters_ros.h"

namespace rotors_control {

TndNominalControllerNode::TndNominalControllerNode() {
  InitializeParams();

  ros::NodeHandle nh;

  cmd_pose_sub_ = nh.subscribe(
      mav_msgs::default_topics::COMMAND_POSE, 1,
      &TndNominalControllerNode::CommandPoseCallback, this);

  cmd_multi_dof_joint_trajectory_sub_ = nh.subscribe(
      mav_msgs::default_topics::COMMAND_TRAJECTORY, 1,
      &TndNominalControllerNode::MultiDofJointTrajectoryCallback, this);

  odometry_sub_ = nh.subscribe(mav_msgs::default_topics::ODOMETRY, 1,
                               &TndNominalControllerNode::OdometryCallback, this);

  motor_velocity_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
      mav_msgs::default_topics::COMMAND_ACTUATORS, 1);
  // mav_msgs::Actuators is data type (https://github.com/ethz-asl/mav_comm/tree/master/mav_msgs/msg)
  //      => see header file: #include <mav_msgs/Actuators.h>
  // mav_msgs::default_topics::COMMAND_ACTUATORS is topic name (= command/motor_speed)
  //      => see https://github.com/ethz-asl/mav_comm/blob/master/mav_msgs/include/mav_msgs/default_topics.h

  tskf_input_pub_ = nh.advertise<mav_msgs::TSKFInput>(
      mav_msgs::default_topics::TSKF_INPUT, 1);

  command_timer_ = nh.createTimer(ros::Duration(0), &TndNominalControllerNode::TimedCommandCallback, this,
                                  true, false);
}

TndNominalControllerNode::~TndNominalControllerNode() { }

void TndNominalControllerNode::InitializeParams() {
  ros::NodeHandle pnh("~");

  // Read parameters from rosparam.
  GetRosParameter(pnh, "z_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.z_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.z_gain_.x());
  GetRosParameter(pnh, "z_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.z_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.z_gain_.y());
  GetRosParameter(pnh, "z_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.z_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.z_gain_.z());
  GetRosParameter(pnh, "phi_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.phi_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.phi_gain_.x());
  GetRosParameter(pnh, "phi_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.phi_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.phi_gain_.y());
  GetRosParameter(pnh, "phi_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.phi_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.phi_gain_.z());
  GetRosParameter(pnh, "teta_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.teta_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.teta_gain_.x());
  GetRosParameter(pnh, "teta_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.teta_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.teta_gain_.y());
  GetRosParameter(pnh, "teta_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.teta_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.teta_gain_.z());
  GetRosParameter(pnh, "psi_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.psi_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.psi_gain_.x());
  GetRosParameter(pnh, "psi_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.psi_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.psi_gain_.y());
  GetRosParameter(pnh, "psi_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.psi_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.psi_gain_.z());
  GetRosParameter(pnh, "x_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.x_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.x_gain_.x());
  GetRosParameter(pnh, "x_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.x_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.x_gain_.y());
  GetRosParameter(pnh, "x_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.x_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.x_gain_.z());
  GetRosParameter(pnh, "y_gain/K1",
                  tnd_nominal_controller_.controller_parameters_.y_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.y_gain_.x());
  GetRosParameter(pnh, "y_gain/K2",
                  tnd_nominal_controller_.controller_parameters_.y_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.y_gain_.y());
  GetRosParameter(pnh, "y_gain/Ki",
                  tnd_nominal_controller_.controller_parameters_.y_gain_.z(),
                  &tnd_nominal_controller_.controller_parameters_.y_gain_.z());
  GetRosParameter(pnh, "pd_gain/Kp",
                  tnd_nominal_controller_.controller_parameters_.pd_gain_.x(),
                  &tnd_nominal_controller_.controller_parameters_.pd_gain_.x());
  GetRosParameter(pnh, "pd_gain/Kd",
                  tnd_nominal_controller_.controller_parameters_.pd_gain_.y(),
                  &tnd_nominal_controller_.controller_parameters_.pd_gain_.y());
  GetVehicleParameters(pnh, &tnd_nominal_controller_.vehicle_parameters_);
  tnd_nominal_controller_.InitializeParameters();

  LOE_.resize(tnd_nominal_controller_.vehicle_parameters_.rotor_configuration_.rotors.size());
  LOE_time_.resize(tnd_nominal_controller_.vehicle_parameters_.rotor_configuration_.rotors.size());
  GetRosParameter(pnh, "lost_control/rotor0",
                  LOE_(0),&LOE_(0));
  GetRosParameter(pnh, "lost_control/rotor1",
                  LOE_(1),&LOE_(1));
  GetRosParameter(pnh, "lost_control/rotor2",
                  LOE_(2),&LOE_(2));
  GetRosParameter(pnh, "lost_control/rotor3",
                  LOE_(3),&LOE_(3));
  GetRosParameter(pnh, "lost_control/rotor4",
                  LOE_(4),&LOE_(4));
  GetRosParameter(pnh, "lost_control/rotor5",
                  LOE_(5),&LOE_(5));

  GetRosParameter(pnh, "lost_moment/rotor0",
                  LOE_time_(0),&LOE_time_(0));
  GetRosParameter(pnh, "lost_moment/rotor1",
                  LOE_time_(1),&LOE_time_(1));
  GetRosParameter(pnh, "lost_moment/rotor2",
                  LOE_time_(2),&LOE_time_(2));
  GetRosParameter(pnh, "lost_moment/rotor3",
                  LOE_time_(3),&LOE_time_(3));
  GetRosParameter(pnh, "lost_moment/rotor4",
                  LOE_time_(4),&LOE_time_(4));
  GetRosParameter(pnh, "lost_moment/rotor5",
                  LOE_time_(5),&LOE_time_(5));

  // TND - Rotor failure simulation (random)
  //  srand (time(NULL));
  // fault_moment_         = rand() % 5 + 1;
  reference_active_ = false;
  // Fin TND
}
void TndNominalControllerNode::Publish() {
}

void TndNominalControllerNode::CommandPoseCallback(
  const geometry_msgs::PoseStampedConstPtr& pose_msg) {
  // Clear all pending commands.
  command_timer_.stop();
  commands_.clear();
  command_waiting_times_.clear();

  mav_msgs::EigenTrajectoryPoint eigen_reference;
  mav_msgs::eigenTrajectoryPointFromPoseMsg(*pose_msg, &eigen_reference);
  commands_.push_front(eigen_reference);

  tnd_nominal_controller_.SetTrajectoryPoint(commands_.front());
  commands_.pop_front();
}

void TndNominalControllerNode::MultiDofJointTrajectoryCallback(
    const trajectory_msgs::MultiDOFJointTrajectoryConstPtr& msg) {

  // Clear all pending commands.
  command_timer_.stop();
  commands_.clear();
  command_waiting_times_.clear();

  const size_t n_commands = msg->points.size();

  if(n_commands < 1){
    ROS_WARN_STREAM("Got MultiDOFJointTrajectory message, but message has no points.");
    return;
  }

  mav_msgs::EigenTrajectoryPoint eigen_reference;

  mav_msgs::eigenTrajectoryPointFromMsg(msg->points.front(), &eigen_reference);
  commands_.push_front(eigen_reference);

  for (size_t i = 1; i < n_commands; ++i) {
    const trajectory_msgs::MultiDOFJointTrajectoryPoint& reference_before = msg->points[i-1];
    const trajectory_msgs::MultiDOFJointTrajectoryPoint& current_reference = msg->points[i];

    mav_msgs::eigenTrajectoryPointFromMsg(current_reference, &eigen_reference);

    commands_.push_back(eigen_reference);
    command_waiting_times_.push_back(current_reference.time_from_start - reference_before.time_from_start);
  }

  // We can trigger the first command immediately.
  tnd_nominal_controller_.SetTrajectoryPoint(commands_.front());
  commands_.pop_front();

  // TND - Rotor failure simulation
  if (!reference_active_) {
      reference_active_ = true;
      reference_time_   = ros::Time::now();
  }
  // Fin TND

  if (n_commands > 1) {     // wait before go to next point
    command_timer_.setPeriod(command_waiting_times_.front());
    command_waiting_times_.pop_front();
    command_timer_.start();
  }
}

void TndNominalControllerNode::TimedCommandCallback(const ros::TimerEvent& e) {
  if(commands_.empty()){
    ROS_WARN("Commands empty, this should not happen here");
    return;
  }

  const mav_msgs::EigenTrajectoryPoint eigen_reference = commands_.front();
  tnd_nominal_controller_.SetTrajectoryPoint(commands_.front());
  commands_.pop_front();
  command_timer_.stop();
  if(!command_waiting_times_.empty()){
    command_timer_.setPeriod(command_waiting_times_.front());
    command_waiting_times_.pop_front();
    command_timer_.start();
  }
}

void TndNominalControllerNode::OdometryCallback(const nav_msgs::OdometryConstPtr& odometry_msg) {
  ros::NodeHandle pnh("~");

  EigenOdometry odometry;
  eigenOdometryFromMsg(odometry_msg, &odometry);
  tnd_nominal_controller_.SetOdometry(odometry);

  Eigen::VectorXd ref_rotor_velocities, ref_rotor_thrusts;

  ros::Time current_time = ros::Time::now();
  ros::Duration Td = current_time - prev_it_;
  prev_it_ = current_time;

  tnd_nominal_controller_.CalculateRotorVelocities(&ref_rotor_velocities,&ref_rotor_thrusts,Td);

  // Sent to TSKF
  if (reference_active_){
    mav_msgs::TSKFInputPtr tskf_input_msg(new mav_msgs::TSKFInput);
    tskf_input_msg->ref_thrusts.clear();
    for (int i = 0; i < ref_rotor_thrusts.size(); i++)
      tskf_input_msg->ref_thrusts.push_back(ref_rotor_thrusts[i]);

    mav_msgs::vectorEigenToMsg(tnd_nominal_controller_.position_W, &tskf_input_msg->position_W);
    mav_msgs::vectorEigenToMsg(tnd_nominal_controller_.velocity_W, &tskf_input_msg->velocity_W);
    mav_msgs::vectorEigenToMsg(tnd_nominal_controller_.euler_angle, &tskf_input_msg->euler_angle);
    mav_msgs::vectorEigenToMsg(tnd_nominal_controller_.euler_rate, &tskf_input_msg->euler_rate);

    tskf_input_msg->header.stamp = odometry_msg->header.stamp;
    tskf_input_pub_.publish(tskf_input_msg);
  }

  /*if (ros::Time::now().toSec() == 5.0){
      std::cout << "[ INFO] [" << ros::WallTime::now() <<
            "]: LOE of " << LOE << "% on namespace " <<  pnh.getNamespace().c_str() << std::endl;
  }*/
  // Rotor failure simulation
  for(unsigned int i=0; i< 6; i++){
    if ((ros::Time::now() - reference_time_).toSec() > LOE_time_(i)){
        ref_rotor_velocities[i] = sqrt(1.0-LOE_(i))*ref_rotor_velocities[i];
    }
  }

  // Sent to Gazebo
  mav_msgs::ActuatorsPtr actuator_msg(new mav_msgs::Actuators);
  actuator_msg->angular_velocities.clear();
  for (int i = 0; i < ref_rotor_velocities.size(); i++)
    actuator_msg->angular_velocities.push_back(ref_rotor_velocities[i]);
  actuator_msg->header.stamp = odometry_msg->header.stamp;

  motor_velocity_reference_pub_.publish(actuator_msg);

}

}

int main(int argc, char** argv) {
  ros::init(argc, argv, "tnd_nominal_controller_node");
  ROS_INFO("Tnd_nominal_controller_node main started");
  rotors_control::TndNominalControllerNode tnd_nominal_controller_node;

  tnd_nominal_controller_node.prev_it_ = ros::Time::now();
  ros::spin();
  return 0;
}
