

MicroROS Robot/14.ROS2基础课程/6、ROS2节点

cd /home/yahboom/a_linux_img/practice/ros_3

ros2 pkg create pkg_topic --build-type ament_python --dependencies rclpy --node-name publisher_demo

 publisher_demo.py
```python
#导入rclpy库

```

colcon build --packages-select pkg_topic
source install/setup.bash


ros2 run pkg_topic publisher_demo
ros2 topic list
ros2 topic echo /topic_demo


# 发布速度控制海龟画圆

ros2 run turtlesim turtlesim_node

ros2 node info /turtlesim

```shell
yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ ros2 node info /turtlesim
/turtlesim
  Subscribers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /turtle1/cmd_vel: geometry_msgs/msg/Twist
  Publishers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /rosout: rcl_interfaces/msg/Log
    /turtle1/color_sensor: turtlesim/msg/Color
    /turtle1/pose: turtlesim/msg/Pose
  Service Servers:
    /clear: std_srvs/srv/Empty
    /kill: turtlesim/srv/Kill
    /reset: std_srvs/srv/Empty
    /spawn: turtlesim/srv/Spawn
    /turtle1/set_pen: turtlesim/srv/SetPen
    /turtle1/teleport_absolute: turtlesim/srv/TeleportAbsolute
    /turtle1/teleport_relative: turtlesim/srv/TeleportRelative
    /turtlesim/describe_parameters: rcl_interfaces/srv/DescribeParameters
    /turtlesim/get_parameter_types: rcl_interfaces/srv/GetParameterTypes
    /turtlesim/get_parameters: rcl_interfaces/srv/GetParameters
    /turtlesim/list_parameters: rcl_interfaces/srv/ListParameters
    /turtlesim/set_parameters: rcl_interfaces/srv/SetParameters
    /turtlesim/set_parameters_atomically: rcl_interfaces/srv/SetParametersAtomically
  Service Clients:

  Action Servers:
    /turtle1/rotate_absolute: turtlesim/action/RotateAbsolute
  Action Clients:
```


ros2 topic echo /turtle1/pose

ros2 topic info /turtle1/pose
ros2 topic info /turtle1/cmd_vel -v

yahboom@yahboom-VM:~/a_linux_img/practice/ros_3$ ros2 interface show geometry_msgs/msg/Twist
// #This expresses velocity in free space broken into its linear and angular parts.

Vector3  linear
	float64 x
	float64 y
	float64 z
Vector3  angular
	float64 x
	float64 y
	float64 z
yahboom@yahboom-VM:~/a_linux_img/practice/ros_3$ ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{angular: {z: 1.0}, linear: {x: 1.0}}"
publisher: beginning loop
publishing #1: geometry_msgs.msg.Twist(linear=geometry_msgs.msg.Vector3(x=1.0, y=0.0, z=0.0), angular=geometry_msgs.msg.Vector3(x=0.0, y=0.0, z=1.0))

publishing #2: geometry_msgs.msg.Twist(linear=geometry_msgs.msg.Vector3(x=1.0, y=0.0, z=0.0), angular=geometry_msgs.msg.Vector3(x=0.0, y=0.0, z=1.0))


# 使用c++ 话题订阅和发布

/mnt/hgfs/a_linux_img/practice/ros_3$ ros2 pkg create turtle_topic_cpp --build-type ament_cmake --dependencies rclcpp geometry_msgs turtlesim --license Apache-2.0

colcon build --packages-select turtle_topic_cpp

```
add_executable(turtle_circle src/turtle_circle.cpp)
ament_target_dependencies(turtle_circle rclcpp geometry_msgs)

install(TARGETS
turtle_circle
DESTINATION lib/${PROJECT_NAME}
)
```



ahboom@yahboom-VM:/mnt/hgfs/a_linux_img/practice/ros_3$ colcon build --packages-select turtle_topic_cpp
Starting >>> turtle_topic_cpp
Finished <<< turtle_topic_cpp [7.23s]                     

Summary: 1 package finished [8.13s]
yahboom@yahboom-VM:/mnt/hgfs/a_linux_img/practice/ros_3$ source install/setup.bash 
yahboom@yahboom-VM:/mnt/hgfs/a_linux_img/practice/ros_3$ ros2 run turtle_topic_cpp turtle_circle 
[INFO] [1758015632.209954375] [rclcpp]: signal_handler(signum=2)




```
add_executable(turtle_circle src/turtle_circle.cpp)
add_executable(turtle_control src/turtle_control.cpp)
ament_target_dependencies(turtle_circle rclcpp geometry_msgs)
ament_target_dependencies(turtle_control rclcpp geometry_msgs turtlesim)

install(TARGETS
turtle_circle
turtle_control
DESTINATION lib/${PROJECT_NAME}
)
```