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

#include "nominal_controller.hpp"

namespace gsft_control {

NominalController::NominalController()
  : initialized_params_(false),
    controller_active_(false) {
  InitializeParameters();
}

NominalController::~NominalController() {}

void NominalController::InitializeParameters() {
  ROS_INFO("Tnd_nominal_controller object initializeParameters");
  position_W.setZero(); velocity_W.setZero(); euler_angle.setZero(); euler_rate.setZero();
  z_int_ = 0.0; psi_int_ = 0.0; phi_int_ = 0.0; teta_int_ = 0.0; x_int_ = 0.0; y_int_ = 0.0;
  initialized_params_ = true;
}
void NominalController::CalculateRotorVelocities(Eigen::VectorXd* rotor_velocities, Eigen::VectorXd* rotor_thrusts, ros::Duration Td) {
  assert(rotor_velocities);
  assert(initialized_params_);

  rotor_velocities->resize(vehicle_parameters_.rotor_configuration_.rotors.size());
  rotor_thrusts->resize(vehicle_parameters_.rotor_configuration_.rotors.size());

  // Return 0 velocities on all rotors, until the first command is received.
  if (!controller_active_) {
    *rotor_velocities = Eigen::VectorXd::Zero(rotor_velocities->rows());
    *rotor_thrusts = Eigen::VectorXd::Zero(rotor_thrusts->rows());
    return;
  }

  Eigen::VectorXd DTz(6);
  ComputeDTz(&DTz,command_trajectory_.position_W.z(),Td);

  Eigen::VectorXd DTpsi(6), DTphi(6), DTteta(6);
  Eigen::Vector3d angle_ref;
  angle_ref.setZero();

  //if (position_W.z() > 1.9){
  ComputeDesiredAttitude(&angle_ref,Td,0);      // 0 = PD controller for XY position, 1 = state feedback controller
  //}

  ComputeDTpsi(&DTpsi,angle_ref.z(),Td);
  ComputeDTphi(&DTphi,angle_ref.x(),Td);
  ComputeDTteta(&DTteta,angle_ref.y(),Td);

  Eigen::VectorXd DTe(6);
  double thrust_e = vehicle_parameters_.mass_ * kDefaultGravity;
  DTe << thrust_e/6.0, thrust_e/6.0, thrust_e/6.0, thrust_e/6.0, thrust_e/6.0, thrust_e/6.0; // 2.5633 N for each rotor <=> 547.5904 rad/s

  //Eigen::VectorXd error_tuning(6);
  //error_tuning << 0.03979, 0.03979, 0.03979, 0.03979, 0.03979, 0.03979;

  Eigen::VectorXd DT(6);
  DT = DTe + DTz + DTphi + DTteta + DTpsi;

/*  std::cout << "[ INFO] [" << ros::Time::now() <<
      "]: ---------- Controller thurst ----------" << DT << std::endl; */

/*  for(unsigned int i=0; i< DT.size(); i++)
      DT[i] = fmin(fmax(DT[i],0),controller_parameters_.max_thrust_);  */

  Eigen::VectorXd omega;
  omega =  DT/vehicle_parameters_.rotor_configuration_.rotors[0].rotor_force_constant;
  for(unsigned int i=0; i< omega.size(); i++)
    omega[i] = sqrt(fmax(omega[i],0.0));

  *rotor_velocities = omega;
  *rotor_thrusts = DT;
/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND DT = " << DT << std::endl;
/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND omega = " << omega << std::endl;*/
}

void NominalController::SetOdometry(const EigenOdometry& odometry) {
  odometry_ = odometry;

  position_W = odometry_.position;
  // https://github.com/libigl/eigen/blob/1f05f51517ec4fd91eed711e0f89e97a7c028c0e/Eigen/src/Geometry/Quaternion.h
  Eigen::Matrix3d R_W_B = odometry_.orientation.toRotationMatrix();
  velocity_W =  R_W_B * odometry_.velocity;

  GetEulerZYX_Mobile_Axis(&euler_angle,R_W_B);

  /*tf::Matrix3x3 R_W_B_tf;
  tf::matrixEigenToTF(R_W_B, R_W_B_tf);   // Eigen::Vector3d ea = R_W_I.eulerAngles(2,1,0) incorrect
  double phi, teta, psi;
  // http://docs.ros.org/api/tf/html/c++/Matrix3x3_8h_source.html
  // https://answers.ros.org/question/58863/incorrect-rollpitch-yaw-values-using-getrpy/
  // http://wiki.ros.org/geometry2/RotationMethods

  R_W_B_tf.getRPY(phi, teta, psi);  // roll, pitch, yaw about fixed axes X, Y, Z
  R_W_B_tf.getEulerYPR(psi, teta, phi);  // get euler angle z-y-z (around rotating axis)
  euler << phi, teta, psi;
*/
  double phi = euler_angle.x(), teta = euler_angle.y(), psi = euler_angle.z();
  Eigen::Matrix3d H;
  H << 1.0, sin(phi)*tan(teta), cos(phi)*tan(teta),
    0.0, cos(phi),           -sin(phi),
    0.0, sin(phi)/cos(teta), cos(phi)/cos(teta);
  euler_rate = H*odometry_.angular_velocity;
  /*  std::cout << "Position World = " << position_W << std::endl;
  std::cout << "Velocity World = " << velocity_W << std::endl;
  std::cout << "Euler angle = "     << euler*180/3.14 << std::endl;
  std::cout << "Euler rate = "     << euler_rate*180/3.14 << std::endl;*/
}
void NominalController::GetEulerZYX_Mobile_Axis(Eigen::Vector3d* euler_angle, Eigen::Matrix3d R_W2B){
  double phi, teta, psi;
  psi = atan2(R_W2B(1,0),R_W2B(0,0));
  phi = atan2(R_W2B(2,1),R_W2B(2,2));
  teta = asin(-R_W2B(2,0));
  *euler_angle << phi, teta, psi;
}

void NominalController::ComputeDesiredAttitude(Eigen::Vector3d* deseriedAttitude, ros::Duration Td, bool state_feedback) {
  double x_ref, teta_ref, y_ref, phi_ref;
  x_ref = command_trajectory_.position_W.x();
  y_ref = command_trajectory_.position_W.y();;

  if (state_feedback) {
    /*    std::cout << "[ INFO] [" << ros::Time::now() <<
             "]: ---------- TND State feedback controller ----------------- " << std::endl; */
    Eigen::Vector2d state;
    Eigen::RowVector2d K_x, K_y;
    double Ki_x, Ki_y;

    K_x << controller_parameters_.x_gain_(0), controller_parameters_.x_gain_(1);
    Ki_x = controller_parameters_.x_gain_(2);
    /*   std::cout << "Kx = " << K_x << std::endl;
       std::cout << "Kix = " << Ki_x << std::endl; */
    state << position_W.x(), velocity_W.x();
    x_int_ += Td.toSec()*(x_ref - position_W.x());
    teta_ref = -K_x*state + Ki_x*x_int_;

    K_y << controller_parameters_.y_gain_(0), controller_parameters_.y_gain_(1);
    Ki_y = controller_parameters_.y_gain_(2);
    /*std::cout << "Ky = " << K_y << std::endl;
    std::cout << "Kiy = " << Ki_y << std::endl;*/
    state << position_W.y(), velocity_W.y();
    y_int_ += Td.toSec()*(y_ref - position_W.y());
    phi_ref = -K_y*state + Ki_y*y_int_;
  }
  else {      // PD controller for XY position
    /*  std::cout << "[ INFO] [" << ros::Time::now() <<
            "]: ---------- TND PD controller ----------------- " << std::endl; */
    double error_x, error_y;
    double Kp, Kd;
    Kp = controller_parameters_.pd_gain_(0);
    Kd = controller_parameters_.pd_gain_(1);

    error_x = x_ref - position_W.x();
    error_y = y_ref - position_W.y();

    teta_ref = Kp*error_x - Kd*velocity_W.x();
    phi_ref = -Kp*error_y + Kd*velocity_W.y();

  }
  // phi_ref = fmin(fmax(phi_ref, -controller_parameters_.max_roll_pitch_),controller_parameters_.max_roll_pitch_);
  // teta_ref = fmin(fmax(teta_ref, -controller_parameters_.max_roll_pitch_),controller_parameters_.max_roll_pitch_);

  *deseriedAttitude << phi_ref, teta_ref, 0.0;
}

void NominalController::SetTrajectoryPoint(
  const mav_msgs::EigenTrajectoryPoint& command_trajectory) {
  command_trajectory_ = command_trajectory;
  controller_active_ = true;
  std::cout << "[ INFO] [" << ros::WallTime::now()  <<
            "]: Nominal Controller active " << std::endl;
}

void NominalController::ComputeDTz(Eigen::VectorXd* DTz,double z_ref,ros::Duration Td) {
  DTz->resize(vehicle_parameters_.rotor_configuration_.rotors.size());
  assert(DTz);

  double a, b, c;
  a = controller_parameters_.z_gain_(0);
  b = controller_parameters_.z_gain_(1);
  c = controller_parameters_.z_gain_(2);
  Eigen::MatrixXd K(6,2);
  Eigen::VectorXd Ki(6);
  K << a/6.0, b/6.0,
    a/6.0, b/6.0,
    a/6.0, b/6.0,
    a/6.0, b/6.0,
    a/6.0, b/6.0,
    a/6.0, b/6.0;
  Ki << c/6.0, c/6.0, c/6.0, c/6.0, c/6.0, c/6.0;

/*  std::cout << "Kz = " << a << "  " << b << std::endl;
  std::cout << "Kiz = " << c << std::endl;*/

  Eigen::Vector2d state;
  state << position_W.z(), velocity_W.z();
  z_int_ += Td.toSec()*(z_ref - position_W.z());

  *DTz = -K*state + Ki*z_int_;
/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND z = " << position_W.z() << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND z_ref = " << z_ref << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND DTz = " << *DTz << std::endl;*/
}

void NominalController::ComputeDTpsi(Eigen::VectorXd* DTpsi,double psi_ref,ros::Duration Td){
  DTpsi->resize(vehicle_parameters_.rotor_configuration_.rotors.size());
  assert(DTpsi);

  double a, b, c, scale;
  scale = vehicle_parameters_.rotor_configuration_.rotors[0].rotor_moment_constant;
  a = controller_parameters_.psi_gain_(0)/(6.0*scale);
  b = controller_parameters_.psi_gain_(1)/(6.0*scale);
  c = controller_parameters_.psi_gain_(2)/(6.0*scale);

/*  std::cout << "Kpsi = " << controller_parameters_.psi_gain_(0) << "  " << controller_parameters_.psi_gain_(1) << std::endl;
  std::cout << "Kipsi = " << controller_parameters_.psi_gain_(2) << std::endl;*/

  Eigen::MatrixXd K(6,2);
  Eigen::VectorXd Ki(6);
  K << -a,-b,
    a,b,
    -a,-b,
    a, b,
    -a,-b,
    a, b;
  Ki << -c, c, -c, c, -c, c;

  Eigen::Vector2d state;
  state << euler_angle.z(), euler_rate.z();
  psi_int_ += Td.toSec()*(psi_ref - euler_angle.z());

  *DTpsi = -K*state + Ki*psi_int_;
/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND psi = " << euler_angle.z()*180/3.14 << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND psi_ref = " << psi_ref*180/3.14 << std::endl;
   std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND DTpsi = " << *DTpsi << std::endl;*/
}

void NominalController::ComputeDTphi(Eigen::VectorXd* DTphi,double phi_ref,ros::Duration Td){
  DTphi->resize(vehicle_parameters_.rotor_configuration_.rotors.size());
  assert(DTphi);

  double a, b, c, arm;
  arm = vehicle_parameters_.rotor_configuration_.rotors[0].arm_length;
  a = controller_parameters_.phi_gain_(0)/(6.0*arm);
  b = controller_parameters_.phi_gain_(1)/(6.0*arm);
  c = controller_parameters_.phi_gain_(2)/(6.0*arm);

/*  std::cout << "Kphi = " << controller_parameters_.phi_gain_(0) << "  " << controller_parameters_.phi_gain_(1) << std::endl;
  std::cout << "Kiphi = " << controller_parameters_.phi_gain_(2) << std::endl;*/

  Eigen::MatrixXd K(6,2);
  Eigen::VectorXd Ki(6);
  K <<   a,   b,
    2.0*a, 2.0*b,
    a,   b,
    -a,  -b,
    -2.0*a,-2.0*b,
    -a,  -b;
  Ki << c, 2.0*c, c, -c, -2.0*c, -c;

  Eigen::Vector2d state;
  state << euler_angle.x(), euler_rate.x();
  phi_int_ += Td.toSec()*(phi_ref - euler_angle.x());

  *DTphi = -K*state + Ki*phi_int_;

/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND phi = " << euler_angle.x()*180/3.14 << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND phi_ref = " << phi_ref*180/3.14 << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND DTphi = " << *DTphi << std::endl; */
}


void NominalController::ComputeDTteta(Eigen::VectorXd* DTteta,double teta_ref,ros::Duration Td){
  DTteta->resize(vehicle_parameters_.rotor_configuration_.rotors.size());
  assert(DTteta);

  double a, b, c, arm;
  arm = vehicle_parameters_.rotor_configuration_.rotors[0].arm_length;
  a = sqrt(3)*controller_parameters_.teta_gain_(0)/(6.0*arm);
  b = sqrt(3)*controller_parameters_.teta_gain_(1)/(6.0*arm);
  c = sqrt(3)*controller_parameters_.teta_gain_(2)/(6.0*arm);

/*  std::cout << "Kteta = " << controller_parameters_.teta_gain_(0) << "  " << controller_parameters_.teta_gain_(1) << std::endl;
  std::cout << "Kiteta = " << controller_parameters_.teta_gain_(2) << std::endl;*/

  Eigen::MatrixXd K(6,2);
  Eigen::VectorXd Ki(6);
  K << -a, -b,
    0.0, 0.0,
    a,b,
    a,b,
    0.0, 0.0,
    -a, -b;
  Ki << -c, 0.0, c, c, 0.0, -c;

  Eigen::Vector2d state;
  state << euler_angle.y(), euler_rate.y();
  teta_int_ += Td.toSec()*(teta_ref - euler_angle.y());

  *DTteta = -K*state + Ki*teta_int_;

/*  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND teta = " << euler_angle.y()*180/3.14 << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND teta_ref = " << teta_ref*180/3.14 << std::endl;
  std::cout << "[ INFO] [" << ros::Time::now() <<
        "]: ---------- TND DTteta = " << *DTteta << std::endl; */
}
}
