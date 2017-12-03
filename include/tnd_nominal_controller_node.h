
#ifndef ROTORS_CONTROL_TND_NOMINAL_CONTROLLER_NODE_H
#define ROTORS_CONTROL_TND_NOMINAL_CONTROLLER_NODE_H

#include <boost/bind.hpp>
#include <Eigen/Eigen>
#include <stdio.h>

#include <geometry_msgs/PoseStamped.h>
#include <mav_msgs/Actuators.h>
#include <mav_msgs/AttitudeThrust.h>
#include <mav_msgs/eigen_mav_msgs.h>
#include <mav_msgs/TSKFInput.h>
#include <nav_msgs/Odometry.h>
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>

#include "rotors_control/common.h"
#include "rotors_control/tnd_nominal_controller.h"

namespace rotors_control {

class TndNominalControllerNode {
 public:
  TndNominalControllerNode();
  ~TndNominalControllerNode();

  void InitializeParams();
  void Publish();

  ros::Time prev_it_;

 private:

  TndNominalController tnd_nominal_controller_;
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

  ros::Publisher motor_velocity_reference_pub_, tskf_input_pub_;

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

#endif // ROTORS_CONTROL_tnd_nominal_CONTROLLER_NODE_H
