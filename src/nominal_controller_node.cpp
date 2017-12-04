/****************************************************************************
 *
 *   Copyright (c) 2017 Mobile Robotics and Autonomous Systems Laboratory
 *   (MRASL), Polytechnique Montreal. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name MRASL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @author  Duc-Tien Nguyen <duc-tien.nguyen@polymtl.ca>
 * @author  Andre Phu-Van Nguyen <andre-phu-van.nguyen@polymtl.ca>
 *
 ****************************************************************************/

#include <ros/ros.h>
#include <mav_msgs/default_topics.h>

#include "nominal_controller_node.hpp"

#include "parameters_ros.h"

namespace gsft_control {

NominalControllerNode::NominalControllerNode() {
  InitializeParams();

  ros::NodeHandle nh;

  cmd_pose_sub_ = nh.subscribe(
    mav_msgs::default_topics::COMMAND_POSE, 1,
    &NominalControllerNode::CommandPoseCallback, this);

  cmd_multi_dof_joint_trajectory_sub_ = nh.subscribe(
    mav_msgs::default_topics::COMMAND_TRAJECTORY, 1,
    &NominalControllerNode::MultiDofJointTrajectoryCallback, this);

  odometry_sub_ = nh.subscribe(mav_msgs::default_topics::ODOMETRY, 1,
                               &NominalControllerNode::OdometryCallback, this);

  motor_velocity_reference_pub_ = nh.advertise<mav_msgs::Actuators>(
    mav_msgs::default_topics::COMMAND_ACTUATORS, 1);
  // mav_msgs::Actuators is data type (https://github.com/ethz-asl/mav_comm/tree/master/mav_msgs/msg)
  //      => see header file: #include <mav_msgs/Actuators.h>
  // mav_msgs::default_topics::COMMAND_ACTUATORS is topic name (= command/motor_speed)
  //      => see https://github.com/ethz-asl/mav_comm/blob/master/mav_msgs/include/mav_msgs/default_topics.h

  //tskf_input_pub_ = nh.advertise<mav_msgs::TSKFInput>(
  //mav_msgs::default_topics::TSKF_INPUT, 1);

  command_timer_ = nh.createTimer(ros::Duration(0), &NominalControllerNode::TimedCommandCallback, this,
                                  true, false);
}

NominalControllerNode::~NominalControllerNode() { }

void NominalControllerNode::InitializeParams() {
  ros::NodeHandle pnh("~");

  // Read parameters from rosparam.
  GetRosParameter(pnh, "z_gain/K1",
                  nominal_controller_.controller_parameters_.z_gain_.x(),
                  &nominal_controller_.controller_parameters_.z_gain_.x());
  GetRosParameter(pnh, "z_gain/K2",
                  nominal_controller_.controller_parameters_.z_gain_.y(),
                  &nominal_controller_.controller_parameters_.z_gain_.y());
  GetRosParameter(pnh, "z_gain/Ki",
                  nominal_controller_.controller_parameters_.z_gain_.z(),
                  &nominal_controller_.controller_parameters_.z_gain_.z());
  GetRosParameter(pnh, "phi_gain/K1",
                  nominal_controller_.controller_parameters_.phi_gain_.x(),
                  &nominal_controller_.controller_parameters_.phi_gain_.x());
  GetRosParameter(pnh, "phi_gain/K2",
                  nominal_controller_.controller_parameters_.phi_gain_.y(),
                  &nominal_controller_.controller_parameters_.phi_gain_.y());
  GetRosParameter(pnh, "phi_gain/Ki",
                  nominal_controller_.controller_parameters_.phi_gain_.z(),
                  &nominal_controller_.controller_parameters_.phi_gain_.z());
  GetRosParameter(pnh, "teta_gain/K1",
                  nominal_controller_.controller_parameters_.teta_gain_.x(),
                  &nominal_controller_.controller_parameters_.teta_gain_.x());
  GetRosParameter(pnh, "teta_gain/K2",
                  nominal_controller_.controller_parameters_.teta_gain_.y(),
                  &nominal_controller_.controller_parameters_.teta_gain_.y());
  GetRosParameter(pnh, "teta_gain/Ki",
                  nominal_controller_.controller_parameters_.teta_gain_.z(),
                  &nominal_controller_.controller_parameters_.teta_gain_.z());
  GetRosParameter(pnh, "psi_gain/K1",
                  nominal_controller_.controller_parameters_.psi_gain_.x(),
                  &nominal_controller_.controller_parameters_.psi_gain_.x());
  GetRosParameter(pnh, "psi_gain/K2",
                  nominal_controller_.controller_parameters_.psi_gain_.y(),
                  &nominal_controller_.controller_parameters_.psi_gain_.y());
  GetRosParameter(pnh, "psi_gain/Ki",
                  nominal_controller_.controller_parameters_.psi_gain_.z(),
                  &nominal_controller_.controller_parameters_.psi_gain_.z());
  GetRosParameter(pnh, "x_gain/K1",
                  nominal_controller_.controller_parameters_.x_gain_.x(),
                  &nominal_controller_.controller_parameters_.x_gain_.x());
  GetRosParameter(pnh, "x_gain/K2",
                  nominal_controller_.controller_parameters_.x_gain_.y(),
                  &nominal_controller_.controller_parameters_.x_gain_.y());
  GetRosParameter(pnh, "x_gain/Ki",
                  nominal_controller_.controller_parameters_.x_gain_.z(),
                  &nominal_controller_.controller_parameters_.x_gain_.z());
  GetRosParameter(pnh, "y_gain/K1",
                  nominal_controller_.controller_parameters_.y_gain_.x(),
                  &nominal_controller_.controller_parameters_.y_gain_.x());
  GetRosParameter(pnh, "y_gain/K2",
                  nominal_controller_.controller_parameters_.y_gain_.y(),
                  &nominal_controller_.controller_parameters_.y_gain_.y());
  GetRosParameter(pnh, "y_gain/Ki",
                  nominal_controller_.controller_parameters_.y_gain_.z(),
                  &nominal_controller_.controller_parameters_.y_gain_.z());
  GetRosParameter(pnh, "pd_gain/Kp",
                  nominal_controller_.controller_parameters_.pd_gain_.x(),
                  &nominal_controller_.controller_parameters_.pd_gain_.x());
  GetRosParameter(pnh, "pd_gain/Kd",
                  nominal_controller_.controller_parameters_.pd_gain_.y(),
                  &nominal_controller_.controller_parameters_.pd_gain_.y());
  GetVehicleParameters(pnh, &nominal_controller_.vehicle_parameters_);
  nominal_controller_.InitializeParameters();

  LOE_.resize(nominal_controller_.vehicle_parameters_.rotor_configuration_.rotors.size());
  LOE_time_.resize(nominal_controller_.vehicle_parameters_.rotor_configuration_.rotors.size());
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
void NominalControllerNode::Publish() {
}

void NominalControllerNode::CommandPoseCallback(
  const geometry_msgs::PoseStampedConstPtr& pose_msg) {
  // Clear all pending commands.
  command_timer_.stop();
  commands_.clear();
  command_waiting_times_.clear();

  mav_msgs::EigenTrajectoryPoint eigen_reference;
  mav_msgs::eigenTrajectoryPointFromPoseMsg(*pose_msg, &eigen_reference);
  commands_.push_front(eigen_reference);

  nominal_controller_.SetTrajectoryPoint(commands_.front());
  commands_.pop_front();
}

void NominalControllerNode::MultiDofJointTrajectoryCallback(
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
  nominal_controller_.SetTrajectoryPoint(commands_.front());
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

void NominalControllerNode::TimedCommandCallback(const ros::TimerEvent& e) {
  if(commands_.empty()){
    ROS_WARN("Commands empty, this should not happen here");
    return;
  }

  const mav_msgs::EigenTrajectoryPoint eigen_reference = commands_.front();
  nominal_controller_.SetTrajectoryPoint(commands_.front());
  commands_.pop_front();
  command_timer_.stop();
  if(!command_waiting_times_.empty()){
    command_timer_.setPeriod(command_waiting_times_.front());
    command_waiting_times_.pop_front();
    command_timer_.start();
  }
}

void NominalControllerNode::OdometryCallback(const nav_msgs::OdometryConstPtr& odometry_msg) {
  ros::NodeHandle pnh("~");

  EigenOdometry odometry;
  eigenOdometryFromMsg(odometry_msg, &odometry);
  nominal_controller_.SetOdometry(odometry);

  Eigen::VectorXd ref_rotor_velocities, ref_rotor_thrusts;

  ros::Time current_time = ros::Time::now();
  ros::Duration Td = current_time - prev_it_;
  prev_it_ = current_time;

  nominal_controller_.CalculateRotorVelocities(&ref_rotor_velocities,&ref_rotor_thrusts,Td);

  // Sent to TSKF
  /*if (reference_active_){
    mav_msgs::TSKFInputPtr tskf_input_msg(new mav_msgs::TSKFInput);
    tskf_input_msg->ref_thrusts.clear();
    for (int i = 0; i < ref_rotor_thrusts.size(); i++)
      tskf_input_msg->ref_thrusts.push_back(ref_rotor_thrusts[i]);

    mav_msgs::vectorEigenToMsg(nominal_controller_.position_W, &tskf_input_msg->position_W);
    mav_msgs::vectorEigenToMsg(nominal_controller_.velocity_W, &tskf_input_msg->velocity_W);
    mav_msgs::vectorEigenToMsg(nominal_controller_.euler_angle, &tskf_input_msg->euler_angle);
    mav_msgs::vectorEigenToMsg(nominal_controller_.euler_rate, &tskf_input_msg->euler_rate);

    tskf_input_msg->header.stamp = odometry_msg->header.stamp;
    tskf_input_pub_.publish(tskf_input_msg);
  }*/

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
  ros::init(argc, argv, "nominal_controller_node");
  ROS_INFO("nominal_controller_node main started");
  gsft_control::NominalControllerNode nominal_controller_node;

  nominal_controller_node.prev_it_ = ros::Time::now();
  ros::spin();
  return 0;
}
