%%
clc; clear all; close all;  

%% Parameters
firefly_parameters;
Ts = 1/60;                       % frequency

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

% augmented system
Aa = [Ac zeros(12,4)
     -Cc zeros(4,4)]; 
Ba = [Bc ; -Dc];

V = ctrb(Aa,Ba);
rank(V)

% Ponderation
%         p            pd           euler        euler_rate    augmented state
Q = diag([10^1*[2 2 5] 10^1*[0.5 0.5 2] 10^1*[1 1 2] 10^0*[1 1 2]  10^2*[0.1 0.1 0.75 0.1]]);        
R = diag(10^1*[0.1 100 100 1000]);

% Observabilit�
M = sqrtm(Q);
U = obsv(Aa,M);
rank(U)

% Calcul du retour d'�tat
K  = lqr(Aa,Ba,Q,R);
for i = 1:size(K,1)
    for j = 1:size(K,2)
        if abs(K(i,j)) < sqrt(eps)
            K(i,j) = 0;
        end
    end
end

Kx_lqr = K(:,1:12)
Ki_lqr = -K(:,13:end)


sys = ss(Ac,Bc,eye(12),zeros(12,4));
sys1 = feedback(sys,Kx_lqr);
s = tf('s');
sys2 = Cc*sys1*Ki_lqr/s;
sys_full = feedback(sys2,eye(4));

step(sys_full,10)

save('K_lqr.mat','Kx_lqr','Ki_lqr','sys_full');
