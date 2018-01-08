clc
clear all

%% 
load bag_data.mat
time_origin = bag_data.rosbag_recv_time(1);        % rosbag_recv_time
final_time  = 1.515427385247280e+09; 

figure(1)
plot(bag_data.rosbag_recv_time-time_origin,bag_data.position_W_x,bag_data.rosbag_recv_time-time_origin,bag_data.position_W_y,bag_data.rosbag_recv_time-time_origin,bag_data.position_W_z)