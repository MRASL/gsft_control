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

## Scenario de test
* Gazebo test
    - Code
      + Simulink Code Generation: 200Hz => Ts = 1/200
      + Node: ros::Rate r(200);
    - Test
      + Launch
        - roslaunch rotors_gazebo mav.launch   
        - roslaunch gsft_control tuning_nominal_Gazebo.launch
      + Gazebo: click run
        - first odometry mesage
        - rqt dynamic reconfigure "gazebo": max_update_rate from 100Hz to 200
        - dynamic reconfigure "firefly/controller": mode, gain, LOE, ... => enable_take_off
* Compare GS and Baseline
    - Code
      + Simulink Code Generation: 200Hz => Ts = 1/200
      + Node: ros::Rate r(200);
      + Cfg
        - controller: enable_take_off = True
        - 
    - Test
      + Launch
        - roslaunch rotors_gazebo mav.launch
        - roslaunch gsft_control tuning_nominal_Gazebo.launch
      + Gazebo: click run => first odometry mesage and rqt dynamic reconfigure "gazebo"
      + rqt
        - dynamic reconfigure "gazebo": max_update_rate = 200
        - dynamic reconfigure "firefly/controller": mode, gain, LOE, ... then click enable_take_off
* Experimental test
    - Code
      + Simulink Code Generation: 1KHz => Ts = 1/1000
      + Node: ros::Rate r(1000);
      + git status, git add, git commit and git push
    - Vicon server: firefly object, 200Hz
    - Ground Station: roslaunch vicon, rqt, rosbag record
    - Asctec Firefly
      + git pull and build
      + roslaunch: fcu, msf, controller
      + check frequencies: Vicon 200HZ, other (imu, msf, controller) 1KHz
