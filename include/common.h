/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Mina Kamel, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Janosch Nikolic, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Modified for the gsft_control project

#ifndef GSFT_CONTROL_COMMON_H
#define GSFT_CONTROL_COMMON_H

#include <assert.h>

#include <mav_msgs/conversions.h>
#include <mav_msgs/default_topics.h>
#include <nav_msgs/Odometry.h>
#include <asctec_hl_comm/MotorSpeed.h>

#include "parameters.h"

// Controller status changed by dynamic reconfigure
#define CONTROLLER_ENABLE            0x01
#define CONTROLLER_REFERENCE         0x02
#define CONTROLLER_GAIN              0x04

namespace gsft_control {
// Default values.
static const std::string kDefaultNamespace = "";
static const std::string kDefaultCommandMotorSpeedTopic =
    mav_msgs::default_topics::COMMAND_ACTUATORS; // "command/motor_speed"
static const std::string kDefaultMotorSpeedTopic =
    mav_msgs::default_topics::MOTOR_MEASUREMENT; // "motor_speed"
static const std::string kDefaultOdometryTopic =
    mav_msgs::default_topics::ODOMETRY; // "odometry"

namespace default_topics {
  static constexpr char LOE[] = "lost_control";
  static constexpr char XYZYAW_ERROR[] = "xyz_yaw_error";
  static constexpr char VIRTUAL_CONTROL[] = "virtual_control";
  static constexpr char UAV_STATE[] = "uav_state";
}

struct EigenOdometry {
  EigenOdometry()
      : position(0.0, 0.0, 0.0),
        orientation(Eigen::Quaterniond::Identity()),
        velocity(0.0, 0.0, 0.0),
        angular_velocity(0.0, 0.0, 0.0) {};

  EigenOdometry(const Eigen::Vector3d& _position,
                const Eigen::Quaterniond& _orientation,
                const Eigen::Vector3d& _velocity,
                const Eigen::Vector3d& _angular_velocity) {
    position = _position;
    orientation = _orientation;
    velocity = _velocity;
    angular_velocity = _angular_velocity;
  };

  Eigen::Vector3d position;
  Eigen::Quaterniond orientation;       // orientation_W_B
  Eigen::Vector3d velocity;             // [u v w] velocity is expressed in the Body frame!
  Eigen::Vector3d angular_velocity;     // [p q r] angular velocity is in the Body frame too!

  inline double getYaw() const { return mav_msgs::yawFromQuaternion(orientation); }
  inline void getEulerAngles(Eigen::Vector3d* euler_angles) const {
    mav_msgs::getEulerAnglesFromQuaternion(orientation, euler_angles);
  }
  inline Eigen::Vector3d getVelocityWorld() const {
    return orientation * velocity;    // orientation_W_B * velocity_B
  }
};


inline void eigenOdometryFromMsg(const nav_msgs::OdometryConstPtr& msg,
                                 EigenOdometry* odometry) {
  odometry->position = mav_msgs::vector3FromPointMsg(msg->pose.pose.position);
  odometry->orientation = mav_msgs::quaternionFromMsg(msg->pose.pose.orientation);
  odometry->velocity = mav_msgs::vector3FromMsg(msg->twist.twist.linear);
  odometry->angular_velocity = mav_msgs::vector3FromMsg(msg->twist.twist.angular);
}

inline void calculateAllocationMatrix(const RotorConfiguration& rotor_configuration,
                                      Eigen::Matrix4Xd* allocation_matrix) {
  assert(allocation_matrix != nullptr);
  allocation_matrix->resize(4, rotor_configuration.rotors.size());
  unsigned int i = 0;
  for (const Rotor& rotor : rotor_configuration.rotors) {
    // Set first row of allocation matrix.
    (*allocation_matrix)(0, i) = sin(rotor.angle) * rotor.arm_length
                                 * rotor.rotor_force_constant;
    // Set second row of allocation matrix.
    (*allocation_matrix)(1, i) = -cos(rotor.angle) * rotor.arm_length
                                 * rotor.rotor_force_constant;
    // Set third row of allocation matrix.
    (*allocation_matrix)(2, i) = -rotor.direction * rotor.rotor_force_constant
                                 * rotor.rotor_moment_constant;
    // Set forth row of allocation matrix.
    (*allocation_matrix)(3, i) = rotor.rotor_force_constant;
    ++i;
  }
  Eigen::FullPivLU<Eigen::Matrix4Xd> lu(*allocation_matrix);
  // Setting the threshold for when pivots of the rank calculation should be considered nonzero.
  lu.setThreshold(1e-9);
  int rank = lu.rank();
  if (rank < 4) {
    std::cout << "The rank of the allocation matrix is " << lu.rank()
              << ", it should have rank 4, to have a fully controllable system,"
              << " check your configuration." << std::endl;
  }

}

inline void skewMatrixFromVector(Eigen::Vector3d& vector, Eigen::Matrix3d* skew_matrix) {
  *skew_matrix << 0, -vector.z(), vector.y(),
                  vector.z(), 0, -vector.x(),
                  -vector.y(), vector.x(), 0;
}

inline void vectorFromSkewMatrix(Eigen::Matrix3d& skew_matrix, Eigen::Vector3d* vector) {
  *vector << skew_matrix(2, 1), skew_matrix(0,2), skew_matrix(1, 0);
}

inline void commandMsg2Thrust(const asctec_hl_comm::MotorSpeedConstPtr& msg,
                                 Eigen::VectorXd* thrust) {
  Eigen::VectorXd temp = Eigen::VectorXd::Zero(msg->motor_speed.size());
   for (unsigned int i=0; i< 6; i++) {
      temp[i] = kDefaultRotorForceConstant*pow(((1250.0 + 43.75*(msg->motor_speed[i]))/9.5493),2);
   }
   *thrust = temp;
}

inline double command2Thrust(double command) {
  return kDefaultRotorForceConstant*pow(((1250.0 + 43.75*(command))/9.5493),2);
}

inline void speedMsg2Thrust(const mav_msgs::ActuatorsConstPtr& msg,
                               Eigen::VectorXd* thrust) {
  Eigen::VectorXd temp = Eigen::VectorXd::Zero(msg->angular_velocities.size());
   for (unsigned int i=0; i< 6; i++) {
      temp[i] = kDefaultRotorForceConstant*pow(msg->angular_velocities[i],2);
   }
   *thrust = temp;
}

}

#endif // GSFT_CONTROL_COMMON_H
