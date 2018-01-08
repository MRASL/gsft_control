%%
clc; clear all; %close all;  

%% Parameters
addpath('../..')
firefly_parameters;
Ts = 1/60;                       % frequency
load K_lqr_hovering_ENU.mat

%%
% X   p      pd      euler   euler_rate 
Ac = [0 0 0  1 0 0   0  0  0  0 0 0     % p
      0 0 0  0 1 0   0  0  0  0 0 0
      0 0 0  0 0 1   0  0  0  0 0 0        
      0 0 0  0 0 0   0 gra 0  0 0 0     % pd
      0 0 0  0 0 0   -gra 0  0  0 0 0
      0 0 0  0 0 0   0  0  0  0 0 0      
      0 0 0  0 0 0   0  0  0  1 0 0     % euler
      0 0 0  0 0 0   0  0  0  0 1 0
      0 0 0  0 0 0   0  0  0  0 0 1       
      0 0 0  0 0 0   0  0  0  0 0 0     % euler_rate
      0 0 0  0 0 0   0  0  0  0 0 0
      0 0 0  0 0 0   0  0  0  0 0 0]; 

  % U   uz  uphi  uteta  upsi
Bc = [zeros(3,4)                     % p  
      zeros(2,4)                     % pd       
      1/mass 0 0 0                     
      zeros(3,4)                     % euler  
      zeros(3,1) diag([1/Ixx, 1/Iyy, 1/Izz])];    % euler_rate

% Y = X
Cc = [eye(3) zeros(3,9)
      zeros(1,8) 1 zeros(1,3)];
Dc = zeros(4,4);

%% Test - NonLinear
%  Fault
tm1  = 10; tm2 = 10; tm3 = 10; tm4 = 10; tm5 = 10; tm6 = 10;
LOE1 = 0; LOE2 = 0; LOE3 = 0; LOE4 = 0; LOE5 = 0; LOE6 = 0;

% 6DOF param init
H_e        = 0;                   % 6DoF Parameters
Vb_e       = [0 0 0]';
Omegab_e   = [0 0 0]';
Po_e       = [0 0 0]';
Euler_e    = [0 0 2*pi]';
g0         = gra;
Ib         = [Ixx  0   0
              0   Iyy  0
              0    0  Izz];

%% Note: NED to ENU
% See 
%     asctec_hl_firmware/sdk.c 
%     asctec_hl_interface/src/ssdk_interface.cpp
%     asctec_hl_firmware/dekf.c
%     asctec_hl_interface/package_doc.txt
%     asctec_hl_comm/include/asctec_hl_comm/extPositionCtrl.h

%   * coordinate system: ENU
%       * x: front
%       * y: left
%       * z: up
%       * yaw: ccw when viewed from top 

%   * coordinate system: NED
%       * x: front
%       * y: right
%       * z: down
%       * yaw: cw when viewed from top 