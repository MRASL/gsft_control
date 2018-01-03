%%
clc; clear all; close all;  

%% Parameters
firefly_parameters;
Ts = 1/60;                         % frequency

%%
% X   z  zd r  p  rd pd
Ac = [0  1  0  0  0  0     % zd
      0  0  0  0  0  0     % zdd
      0  0  0  0  1  0     % rd
      0  0  0  0  0  1     % pd
      0  0  0  0  0  0     % rdd
      0  0  0  0  0  0];   % pdd


  % U uz uphi uteta   
Bc = [0   0   0            % zd
   1/mass 0   0            % zdd
      zeros(2,3)           % rpd
      0 1/Ixx 0
      0  0   1/Iyy];
Cc = [1 0 0 0 0 0 
      0 0 1 0 0 0
      0 0 0 1 0 0];

Dc = zeros(3,3);
ss(Ac, Bc, Cc, Dc)

% augmented system
Aa = [Ac zeros(6,3)
     -Cc zeros(3,3)]; 
Ba = [Bc ; -Dc];

V = ctrb(Aa,Ba);
rank(V)

% Ponderation
%           z     zd     RP         RPd        augmented
Q = diag([10^1*5 10^1*2 10^1*[1 1] 10^0*[1 1]  10^2*[0.75 0.1 0.1]]);        
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

Kx_lqr = K(:,1:6)
Ki_lqr = -K(:,7:end)


sys = ss(Ac,Bc,eye(6),zeros(6,3));
sys1 = feedback(sys,Kx_lqr);
s = tf('s');
sys2 = Cc*sys1*Ki_lqr/s;
sys_inner = feedback(sys2,eye(3));

step(sys_inner,10)

save('K_lqr.mat','Kx_lqr','Ki_lqr','sys_inner');

sim('lqr_test')

