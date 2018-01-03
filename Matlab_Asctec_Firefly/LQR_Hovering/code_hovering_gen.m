clc; close all; clear all

%%
firefly_parameters

%%
Ts = 1/60;

%%
load K_lqr


% %% Test
% % X   p      pd      euler   euler_rate 
% Ac = [0 0 0  1 0 0   0  0  0  0 0 0     % p
%       0 0 0  0 1 0   0  0  0  0 0 0
%       0 0 0  0 0 1   0  0  0  0 0 0        
%       0 0 0  0 0 0   0 gra 0  0 0 0     % pd
%       0 0 0  0 0 0   -gra 0  0  0 0 0
%       0 0 0  0 0 0   0  0  0  0 0 0      
%       0 0 0  0 0 0   0  0  0  1 0 0     % euler
%       0 0 0  0 0 0   0  0  0  0 1 0
%       0 0 0  0 0 0   0  0  0  0 0 1       
%       0 0 0  0 0 0   0  0  0  0 0 0     % euler_rate
%       0 0 0  0 0 0   0  0  0  0 0 0
%       0 0 0  0 0 0   0  0  0  0 0 0]; 
% 
%   % U   uz  uphi  uteta  upsi
% Bc = [zeros(3,4)                     % p  
%       zeros(2,4)                     % pd       
%       1/mass 0 0 0                     
%       zeros(3,4)                     % euler  
%       zeros(3,1) diag([1/Ixx, 1/Iyy, 1/Izz])];    % euler_rate
% 
% % Y = X
% Cc = [eye(3) zeros(3,9)
%       zeros(1,8) 1 zeros(1,3)];
% Dc = zeros(4,4);