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

#ifndef GSFT_CONTROL_NOMINAL_CONTROLLER_NODE_HPP
#define GSFT_CONTROL_NOMINAL_CONTROLLER_NODE_HPP

#include <boost/bind.hpp>
#include <Eigen/Eigen>
#include <stdio.h>

#include <geometry_msgs/PoseStamped.h>
#include <mav_msgs/Actuators.h>
#include <mav_msgs/AttitudeThrust.h>
#include <mav_msgs/eigen_mav_msgs.h>
//#include <mav_msgs/TSKFInput.h>
#include <nav_msgs/Odometry.h>
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>

#include "common.h"
#include "nominal_controller.hpp"

namespace gsft_control {
class NominalControllerNode {
public:
  NominalControllerNode();
  ~NominalControllerNode();

  void InitializeParams();
  void Publish();

  ros::Time prev_it_;

private:

  NominalController nominal_controller_;
  std::string namespace_;
  // TND - Rotor failure simulation
  bool reference_active_;
  ros::Time reference_time_;
  // Fin TND
  // subscribers
  ros::Subscriber cmd_trajectory_sub_;
  ros::Subscriber cmd_multi_dof_joint_trajectory_sub_;
  ros::Subscriber cmd_pose_sub_;
  ros::Subscriber odometry_sub_;

  ros::Publisher motor_velocity_reference_pub_;//, tskf_input_pub_;

  mav_msgs::EigenTrajectoryPointDeque commands_;

  std::deque<ros::Duration> command_waiting_times_;
  ros::Timer command_timer_;

  Eigen::VectorXd LOE_;
  Eigen::VectorXd LOE_time_;

  void TimedCommandCallback(const ros::TimerEvent& e);

  void MultiDofJointTrajectoryCallback(
    const trajectory_msgs::MultiDOFJointTrajectoryConstPtr& trajectory_reference_msg);

  void CommandPoseCallback(
    const geometry_msgs::PoseStampedConstPtr& pose_msg);

  void OdometryCallback(const nav_msgs::OdometryConstPtr& odometry_msg);

  inline void EigenToGeometry(Eigen::Vector3d& ev, geometry_msgs::Vector3& gv);
};
}

#endif // GSFT_CONTROL_NOMINAL_CONTROLLER_NODE_HPP