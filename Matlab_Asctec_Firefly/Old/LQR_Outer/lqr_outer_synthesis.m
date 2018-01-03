%%
clc; clear all; close all;  

%% Parameters
firefly_parameters;
Ts = 1/60;                       % frequency

%%
% X   p      pd      RP    RP_rate 
Ac = [0 0 0  1 0 0   0  0  0  0       % p
      0 0 0  0 1 0   0  0  0  0  
      0 0 0  0 0 1   0  0  0  0         
      0 0 0  0 0 0   0 gra 0  0       % pd
      0 0 0  0 0 0 -gra 0  0  0 
      0 0 0  0 0 0   0  0  0  0        
      0 0 0  0 0 0   0  0  1  0       % RP
      0 0 0  0 0 0   0  0  0  1          
      0 0 0  0 0 0   0  0  0  0       % RP_Rate
      0 0 0  0 0 0   0  0  0  0]; 

  % U   uz  uphi  uteta  
Bc = [zeros(3,3)                     % p  
      zeros(2,3)                     % pd       
      1/mass 0 0                      
      zeros(2,3)                     % RP  
      zeros(2,1) diag([1/Ixx, 1/Iyy])];    % RP_rate

% Y = X

% 
Cc = [eye(3) zeros(3,7)];
Dc = zeros(3,3); 

% augmented system
Aa = [Ac zeros(10,3)
     -Cc zeros(3,3)]; 
Ba = [Bc ; -Dc];

V = ctrb(Aa,Ba);
rank(V)

% Ponderation
%         p            pd             RP         RP_rate    augmented state
Q = diag([10^1*[2 2 5] 10^1*[0.5 0.5 2] 10^1*[1 1] 10^0*[1 1]  10^2*[0.1 0.1 0.75]]);        
R = diag(10^1*[0.1 100 100]);

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

Kx_lqr = K(:,1:10)
Ki_lqr = -K(:,11:end)


sys = ss(Ac,Bc,eye(10),zeros(10,3));
sys1 = feedback(sys,Kx_lqr);
s = tf('s');
sys2 = Cc*sys1*Ki_lqr/s;
sys_outer = feedback(sys2,eye(3));

step(sys_outer,10)

save('K_lqr.mat','Kx_lqr','Ki_lqr','sys_outer');