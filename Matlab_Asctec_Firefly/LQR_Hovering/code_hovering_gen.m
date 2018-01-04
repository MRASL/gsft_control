clc; close all; clear all

%% Parameters
addpath('..')

firefly_parameters

%%
Ts = 1/60;

%%
load synthesis/K_lqr_hovering_ENU.mat