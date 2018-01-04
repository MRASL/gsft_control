#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <gsft_control/ControllerDynConfig.h>

void controller_dyn_callback(gsft_control::ControllerDynConfig &config, uint32_t level) {
//  ROS_INFO("Reconfigure Request: %s",
//            config.start_controller?"True":"False");
  ROS_INFO("Reconfigure Request: %d ",
            config.int_param);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "main_node");

  dynamic_reconfigure::Server<gsft_control::ControllerDynConfig> server;
  dynamic_reconfigure::Server<gsft_control::ControllerDynConfig>::CallbackType f;

  f = boost::bind(&controller_dyn_callback, _1, _2);
  server.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
