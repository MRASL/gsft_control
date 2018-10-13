# Gain Scheduling Fault Tolerant Control
By Duc-Tien Nguyen and friends.

## References
If you use this work, please cite one of these publications

Duc-Tien Nguyen, David Saussié, Lahcen Saydy, [Robust Self-Scheduled Fault-Tolerant Control of a Quadrotor UAV](https://doi.org/10.1016/j.ifacol.2017.08.1141), In IFAC-PapersOnLine, Volume 50, Issue 1, 2017, Pages 5761-5767.
```
@article{NGUYEN20175761,
  annote = {20th IFAC World Congress},
  author = {Nguyen, Duc-Tien and Saussi{\'{e}}, David and Saydy, Lahcen},
  doi = {https://doi.org/10.1016/j.ifacol.2017.08.1141},
  issn = {2405-8963},
  journal = {IFAC-PapersOnLine},
  number = {1},
  pages = {5761--5767},
  title = {{Robust Self-Scheduled Fault-Tolerant Control of a Quadrotor UAV}},
  volume = {50},
  year = {2017}
}
```

D. T. Nguyen, D. Saussie and L. Saydy, [Quaternion-based robust fault-tolerant control of a quadrotor UAV](http://ieeexplore.ieee.org/document/7991516/), 2017 International Conference on Unmanned Aircraft Systems (ICUAS), Miami, FL, USA, 2017, pp. 1333-1342.
doi: 10.1109/ICUAS.2017.7991516

```
@inproceedings{nguyen2017quatftc,
  author={D. T. Nguyen and D. Saussie and L. Saydy},
  booktitle={2017 International Conference on Unmanned Aircraft Systems (ICUAS)},
  title={Quaternion-based robust fault-tolerant control of a quadrotor UAV},
  year={2017},
  volume={},
  number={},
  pages={1333-1342},
  doi={10.1109/ICUAS.2017.7991516},
  month={June}
}
```

# Test guide
## Gazebo Clock
Gazebo -> World -> Physics OR rqt -> gazebo dynamic_reconfigure (appears after unpaused)
  * `max_step_size` (Gazebo) or `time_step` (rqt): for example max_step_size = 0.01sec <=> max_step_freq = 100Hz
    + gazebo object topics at 100Hz (/imu, /motor_speed, ...)
    + posibility to publish messages at maximum 2*100Hz = 200Hz (/command/motor_speed, ...)
  * `real_time_update_rate` (Gazebo) or `max_update_rate` (rqt): 0 - 1KHZ => gazebo video speed
  * `time_factor` = `real_time_update_rate/max_step_freq`
    + real_time_update_rate = max_step_freq: time_factor = 1 => normal gazebo video speed (sim time = real time)
    + real_time_update_rate < max_step_freq: time_factor < 1 => slow gazebo video speed (sim time < real time)
    + real_time_update_rate > max_step_freq: incorrect dynamic simulation, can cause crash if time_factor too big

## Gazebo test
  * 1 mav test
      + Gazebo
        - `roslaunch rotors_gazebo mav.launch`
        - change max_step_size = 0.001, then real_time_update_rate = 1000Hz (must after max_step_size)
      + Controller
        - `roslaunch gsft_control tuning_nominal_Gazebo.launch`
        - dynamic reconfigure "firefly/controller": mode, gain, LOE, ...
      + Run
        - Gazebo: click run => saw first odometry mesage
        - Controller: click enable_take_off
  * 2 mav compare test: same as 1 mav test except
      + `mav_2.launch` and `tuning_compare_Gazebo.launch`
      + click run (Gazebo) after chose enable_take_off (to compare 2 mav but can not click 2 enable_take_off buttons at the same time)

## Gazebo videos
  * Slow video speed: real time_factor is lowered (machine cannot handle computing with the given parameters)
    + 1 mav: max_step_freq = real_time_update_rate = 1kHz but time factor = 0.5 => 1/2 slow video speed
    + 2 mav: max_step_freq = real_time_update_rate = 1kHz but time factor = 0.25 => 1/4 slow video speed
  * 1 mav test
    + Solution 1: test performed at 500Hz (both Gazebo and controller)
        - max_step_size = 0.002, real_time_update_rate = 500Hz
        - modifying Simulink code generation Ts = 1/500 and ros::Rate r(500)
    + Solution 2: Gazebo at 500Hz but controller still at 1kHz  
        - max_step_size = 0.002 and real_time_update_rate = 500Hz => /imu, /odometry, ... available at 500Hz
        - Ts = 1/1000 and ros::Rate r(1000) => still able to publish /motor_speed at 1kHz (see above)
        - degraded performance controller but still acceptable
  * 2 mav test: test have to be performed at < 250Hz (both Gazebo and controller) because of big degraded performance if Gazebo at max freq 250Hz but controller still at 1kHz

## Experimental test
  * Code
      + Simulink Code Generation: 1KHz => Ts = 1/1000
      + Node: ros::Rate r(1000);
      + git status, git add, git commit and git push
  * Vicon server: calibration (at least once a day), chose firefly object, 200Hz
  * Asctec Firefly
      + git pull and build
      + **kill default autopilot rosnodes (clearpath)**
      + launch: fcu, msf, controller
  * Ground Station: ros_vrpn_client mrasl_vicon.launch, rqt => init filter and !!! verify filter output !!!
  * Test
      + check frequencies: Vicon -> 200HZ, state and command (imu, odometry, /fcu/command/direct_motor) -> 1kHz
      + **check battery (fcu/status)**
      + **check manual mode before turn on motor**, rosbag record
      + **check error (fcu, msf)**
      + **check /fcu/command/direct_motor = 0**
      + pass to automatic mode then click enable_take_off
