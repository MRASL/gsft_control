clc
clear all
close all

%% 
load bag_data.mat
addpath('..')

firefly_param_test

for i = 1:length(bag_data.rosbag_recv_time)
    if (bag_data.position_ref_z(i) == 0.5)
        time_origin = bag_data.rosbag_recv_time(i);
        i_begin = i;
        break
    end
end
test_time = bag_data.rosbag_recv_time(i_begin:end)-time_origin;

%% Position & heading
figure() 
subplot(2,3,1)
plot(test_time,bag_data.position_ref_x(i_begin:end),test_time,bag_data.position_W_x(i_begin:end))
title('x'); grid on; xlabel('time (s)'); ylabel('x (m)'); axis([0,120,-1.5,0.5])
subplot(2,3,2)
plot(test_time,bag_data.position_ref_y(i_begin:end),test_time,bag_data.position_W_y(i_begin:end))
title('y'); grid on; xlabel('time (s)'); ylabel('y (m)'); axis([0,120,-0.5,1.5])
subplot(2,3,3)
plot(test_time,bag_data.position_ref_z(i_begin:end),test_time,bag_data.position_W_z(i_begin:end))
title('z'); grid on; xlabel('time (s)'); ylabel('z (m)'); axis([0,120,0,0.6])
subplot(2,3,4)
plot(bag_data.euler_angle_x(i_begin:end)*180/pi)
title('roll'); grid on; xlabel('time (s)'); ylabel('phi (deg)');% axis([0,120,-10,40])
subplot(2,3,5)
plot(test_time,bag_data.euler_angle_y(i_begin:end)*180/pi)
title('pitch'); grid on; xlabel('time (s)'); ylabel('teta (deg)'); %axis([0,120,-10,40])
subplot(2,3,6)
plot(test_time,bag_data.heading_ref(i_begin:end)*180/pi,test_time,bag_data.euler_angle_z(i_begin:end)*180/pi)
title('yaw'); grid on; xlabel('time (s)'); ylabel('psi (deg)'); axis([0,120,-10,40])

%% Vitesse
figure() 
subplot(2,1,1)
plot(test_time,bag_data.velocity_W_x(i_begin:end)); hold on
plot(test_time,bag_data.velocity_W_y(i_begin:end)); hold on
plot(test_time,bag_data.velocity_W_z(i_begin:end))
legend('Vx','Vy','Vz')
title('Velocity'); grid on; xlabel('time (s)'); ylabel('m/s'); %axis([0,120,-1.5,0.5])

subplot(2,1,2)
plot(test_time,bag_data.euler_rate_x(i_begin:end)*180/pi); hold on
plot(test_time,bag_data.euler_rate_y(i_begin:end)*180/pi); hold on
plot(test_time,bag_data.euler_rate_z(i_begin:end)*180/pi)
legend('phi\_dot','teta\_dot','psi\_dot')
title('Angular velocity'); grid on; xlabel('time (s)'); ylabel('deg/s'); %axis([0,120,-1.5,0.5])


%% Virtual control
figure()
virtual = [bag_data.total_thrust(i_begin:end) bag_data.moment_x(i_begin:end) bag_data.moment_y(i_begin:end) bag_data.moment_z(i_begin:end)];
subplot(2,2,1)
plot(test_time,virtual(:,1))
title('total thrust'); grid on; xlabel('time (s)'); ylabel('T (N)');
subplot(2,2,2)
plot(test_time,virtual(:,2))
title('moment x'); grid on; xlabel('time (s)'); ylabel('Mx (Nm)');axis([0,120,-0.4,0.4])
subplot(2,2,3)
plot(test_time,virtual(:,3))
title('moment y'); grid on; xlabel('time (s)'); ylabel('My (Nm)');axis([0,120,-0.4,0.4])
subplot(2,2,4)
plot(test_time,virtual(:,4))
title('moment z'); grid on; xlabel('time (s)'); ylabel('Mz (Nm)'); axis([0,120,-0.1,0.1])

%% Motor RPM
figure()
title('Motor RPM reference')
for i = 1:size(virtual,1)
    motor_rads(i,1:6) = sqrt(max((B_ENU_inv*virtual(i,:)')./KT,0));
    motor_rpm(i,1:6) = motor_rads(i,1:6)*9.5493;
end
subplot(2,3,1)
plot(test_time,motor_rpm(:,1))
title('motor 1'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(2,3,2)
plot(test_time,motor_rpm(:,2))
title('motor 2'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(2,3,3)
plot(test_time,motor_rpm(:,3))
title('motor 3'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(2,3,4)
plot(test_time,motor_rpm(:,4))
title('motor 4'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(2,3,5)
plot(test_time,motor_rpm(:,5))
title('motor 5'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(2,3,6)
plot(test_time,motor_rpm(:,6))
title('motor 6'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])

%% Motor command 0 .. 200
figure()
title('Normalized control')
for i = 1:size(virtual,1)
    motor_command(i,1:6) = (motor_rpm(i,:) - 1250)/43.75;
end
subplot(2,3,1)
plot(test_time,motor_command(:,1))
title('motor 1'); grid on; xlabel('time (s)'); ylabel('u1'); axis([0,120,80,130])
subplot(2,3,2)
plot(test_time,motor_command(:,2))
title('motor 2'); grid on; xlabel('time (s)'); ylabel('u2'); axis([0,120,80,130])
subplot(2,3,3)
plot(test_time,motor_command(:,3))
title('motor 3'); grid on; xlabel('time (s)'); ylabel('u3'); axis([0,120,80,130])
subplot(2,3,4)
plot(test_time,motor_command(:,4))
title('motor 4'); grid on; xlabel('time (s)'); ylabel('u4'); axis([0,120,80,130])
subplot(2,3,5)
plot(test_time,motor_command(:,5))
title('motor 5'); grid on; xlabel('time (s)'); ylabel('u5'); axis([0,120,80,130])
subplot(2,3,6)
plot(test_time,motor_command(:,6))
title('motor 6'); grid on; xlabel('time (s)'); ylabel('u6'); axis([0,120,80,130])

%%
figure()
title('Control')
subplot(1,3,1)
plot(test_time,motor_rads(:,1),test_time,motor_rads(:,2),test_time,motor_rads(:,3),...
     test_time,motor_rads(:,4),test_time,motor_rads(:,5),test_time,motor_rads(:,6))
title('Motor speed rad/s'); grid on; xlabel('time (s)'); ylabel('rad/s'); axis([0,120,500,750])
subplot(1,3,2)
plot(test_time,motor_rpm(:,1),test_time,motor_rpm(:,2),test_time,motor_rpm(:,3),...
     test_time,motor_rpm(:,4),test_time,motor_rpm(:,5),test_time,motor_rpm(:,6))
title('Motor rpm'); grid on; xlabel('time (s)'); ylabel('rpm'); axis([0,120,5000,7000])
subplot(1,3,3)
plot(test_time,motor_command(:,1),test_time,motor_command(:,2),test_time,motor_command(:,3),...
     test_time,motor_command(:,4),test_time,motor_command(:,5),test_time,motor_command(:,6))
title('Motor command'); grid on; xlabel('time (s)'); axis([0,120,80,130])


%%
% http://wiki.asctec.de/display/AR/List+of+all+predefined+variables%2C+commands+and+parameters
motor_command_max = 200;
motor_rpm_max     = 1250 + motor_command_max*43.75;     % 10000 RPM
motor_speed_max   = 10000*(60/2/pi);                    % ~ 9549.3 rad/s

% equilibrium
k     = find(test_time>10,1);
k_end = find(test_time>20,1);
Th_e  = mean(virtual(k:k_end,1))

% KT identification
KT_iden = mass*gra/KT
