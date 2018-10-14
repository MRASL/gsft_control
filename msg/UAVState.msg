Header header

# references
geometry_msgs/Vector3 position_ref
float64 heading_ref

# state
geometry_msgs/Vector3 position_W
geometry_msgs/Vector3 velocity_W
geometry_msgs/Vector3 euler_angles
geometry_msgs/Vector3 rotation_speed_B

# virtual control
float64 total_thrust
geometry_msgs/Vector3 moment

geometry_msgs/Vector3 thrust_pre
geometry_msgs/Vector3 thrust_after
geometry_msgs/Vector3 vel_Kalman
geometry_msgs/Vector3 acc_Kalman
geometry_msgs/Vector3 M_Kalman

# gain
float64 Kiz
