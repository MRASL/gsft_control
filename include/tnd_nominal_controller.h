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

#ifndef ROTORS_CONTROL_TND_NOMINAL_CONTROLLER_H
#define ROTORS_CONTROL_TND_NOMINAL_CONTROLLER_H

#include <mav_msgs/conversions.h>
#include <mav_msgs/eigen_mav_msgs.h>

#include <tf_conversions/tf_eigen.h>

#include "rotors_control/common.h"
#include "rotors_control/parameters.h"

#include <tf/tf.h>

namespace rotors_control {

// Default values for the TND nominal controller and the Asctec Firefly.
static const Eigen::Vector3d kDefaultPositionGain = Eigen::Vector3d(6, 6, 6);
static const Eigen::Vector3d kDefaultVelocityGain = Eigen::Vector3d(4.7, 4.7, 4.7);
static const Eigen::Vector3d kDefaultAttitudeGain = Eigen::Vector3d(3, 3, 0.035);
static const Eigen::Vector3d kDefaultAngularRateGain = Eigen::Vector3d(0.52, 0.52, 0.025);
static const Eigen::Vector3d kDefaultZGain = Eigen::Vector3d(-6.2712, -4.7034, -3.1356);
static const Eigen::Vector3d kDefaultPhiGain = Eigen::Vector3d(7.5073, 0.8341, 30.0292);
static const Eigen::Vector3d kDefaultTetaGain = Eigen::Vector3d(9.9129, 1.1014, 39.6515);
static const Eigen::Vector3d kDefaultPsiGain = Eigen::Vector3d(0.3908, 0.2931, 0.1954);
static const Eigen::Vector3d kDefaultXGain = Eigen::Vector3d(0.4077, 0.3058, 0.2039);
static const Eigen::Vector3d kDefaultYGain = Eigen::Vector3d(-0.4077, -0.3058, -0.2039);
static const Eigen::Vector2d kDefaultPDGain = Eigen::Vector2d(0.05, 0.1);
static const double max_roll_pitch = 0.5236;   // UAV roll/pitch max = pi/6, Tmax = 6N
static const double max_thrust = 6;            // rotor Thrust max = 6N (firefly)

class TndNominalControllerParameters {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  TndNominalControllerParameters()
      : position_gain_(kDefaultPositionGain),
        velocity_gain_(kDefaultVelocityGain),
        attitude_gain_(kDefaultAttitudeGain),
        angular_rate_gain_(kDefaultAngularRateGain),
        z_gain_(kDefaultZGain),
        phi_gain_(kDefaultPhiGain),
        teta_gain_(kDefaultTetaGain),
        psi_gain_(kDefaultPsiGain),
        x_gain_(kDefaultXGain),
        y_gain_(kDefaultYGain),
        pd_gain_(kDefaultPDGain),
        max_thrust_(max_thrust),
        max_roll_pitch_(max_roll_pitch) {
    calculateAllocationMatrix(rotor_configuration_, &allocation_matrix_);
  }

  Eigen::Matrix4Xd allocation_matrix_;
  Eigen::Vector3d position_gain_;
  Eigen::Vector3d velocity_gain_;
  Eigen::Vector3d attitude_gain_;
  Eigen::Vector3d angular_rate_gain_;
  Eigen::Vector3d z_gain_;
  Eigen::Vector3d phi_gain_;
  Eigen::Vector3d teta_gain_;
  Eigen::Vector3d psi_gain_;
  Eigen::Vector3d x_gain_;
  Eigen::Vector3d y_gain_;
  Eigen::Vector2d pd_gain_;
  double max_thrust_, max_roll_pitch_;
  RotorConfiguration rotor_configuration_;
};

class TndNominalController {
 public:
  TndNominalController();
  ~TndNominalController();
  void InitializeParameters();
  void CalculateRotorVelocities(Eigen::VectorXd* rotor_velocities, Eigen::VectorXd* rotor_thrusts, ros::Duration Td);

  void SetOdometry(const EigenOdometry& odometry);
  void GetEulerZYX_Mobile_Axis(Eigen::Vector3d* euler_angle, Eigen::Matrix3d R_W2B);
  void SetTrajectoryPoint(
    const mav_msgs::EigenTrajectoryPoint& command_trajectory);

  TndNominalControllerParameters controller_parameters_;
  VehicleParameters vehicle_parameters_;

  Eigen::Vector3d position_W, velocity_W, euler_angle, euler_rate;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
 private:
  bool initialized_params_;
  bool controller_active_;


  mav_msgs::EigenTrajectoryPoint command_trajectory_;
  EigenOdometry odometry_;

  double z_int_, psi_int_, phi_int_, teta_int_, x_int_, y_int_;
//  , x_int_, y_int_,  teta_int_,
  void ComputeDTz(Eigen::VectorXd* DTz,double z_ref,ros::Duration Td);
  void ComputeDTpsi(Eigen::VectorXd* DTpsi,double psi_ref,ros::Duration Td);
  void ComputeDTphi(Eigen::VectorXd* DTphi,double phi_ref,ros::Duration Td);
  void ComputeDTteta(Eigen::VectorXd* DTteta,double teta_ref,ros::Duration Td);

  void ComputeDesiredAttitude(Eigen::Vector3d* deseriedAttitude,ros::Duration Td, bool state_feedback);
};
}

#endif // ROTORS_CONTROL_TND_NOMINAL_CONTROLLER_H
