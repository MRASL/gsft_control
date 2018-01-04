#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <gsft_control/controllerDynConfig.h>

void controller_dyn_callback(gsft_control::controllerDynConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %s",
            config.start_controller?"True":"False");
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "main_node");

  dynamic_reconfigure::Server<gsft_control::controllerDynConfig> server;
  dynamic_reconfigure::Server<gsft_control::controllerDynConfig>::CallbackType f;

  f = boost::bind(&controller_dyn_callback, _1, _2);
  server.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
