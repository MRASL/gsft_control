%%  Parameters

% mass  = 1.490;          % without cameras
mass  = 1.5435;           % with cameras


% mass  = 1.56779;      % ethz-asl/rotors_simulator (Gazebo)

gra   = 9.80665;

% https://github.com/ethz-asl/rotors_simulator 
arm   = 0.215;                  
Ixx   = 0.0347563;       Iyy = 0.0458929;    Izz    = 0.0977;
KT    = 0.00000854858;   KD  = KT*0.016;     factor = 0.016;
w_max = 838;             T_max = KT*w_max^2;

alpha = KD/KT/Izz;      a_phi = arm/Ixx;      a_teta = sqrt(3)*arm/Iyy/2;

% Control allocation: Hexarotors
% Reference:
B_ENU =  [1 1 1 1 1 1
          arm/2 arm arm/2 -arm/2 -arm -arm/2;
          -sqrt(3)/2*arm 0 sqrt(3)/2*arm sqrt(3)/2*arm 0 -sqrt(3)/2*arm;
          -factor factor -factor factor -factor factor];  
B_ENU_inv = pinv(B_ENU);

B_NED =  [1 1 1 1 1 1
         arm/2 arm arm/2 -arm/2 -arm -arm/2;
         sqrt(3)/2*arm 0 -sqrt(3)/2*arm -sqrt(3)/2*arm 0 sqrt(3)/2*arm;
         factor -factor factor -factor factor -factor];  

% Control Input Filter 
% https://github.com/ethz-asl/rotors_simulator/blob/2cb6dfbd914a992002d533d11d05630a2eb276ad/rotors_gazebo_plugins/include/rotors_gazebo_plugins/common.h
time_constant_up   = 0.0125;
time_constant_down = 0.025;

tau   = time_constant_up;
A_fil = diag(-1/tau*[1 1 1 1 1 1]);
B_fil = diag(1/tau*[1 1 1 1 1 1]);
C_fil = eye(6);
D_fil = zeros(6,6);