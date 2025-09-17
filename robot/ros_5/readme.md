# 基础服务
ros2 interface show example_interfaces/srv/AddTwoInts 
int64 a
int64 b
---
int64 sum


ros2 pkg create pkg_service --build-type ament_python --dependencies rclpy --node-name server_demo


yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ colcon build --packages-select pkg_service


yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ source install/setup.bash 
yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ ros2 run pkg_service server_demo



yahboom@yahboom-VM:/mnt/hgfs/a_linux_img/practice/ros_4$ ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 1, b: -22}"
requester: making request: example_interfaces.srv.AddTwoInts_Request(a=1, b=-22)


response:
example_interfaces.srv.AddTwoInts_Response(sum=-21)


ros2 pkg create pkg_service --build-type ament_python --dependencies rclpy --node-name client_demo

# 继续玩乌龟

ROS2 topic 提供了单向数据传递的机制，服务通信 service 被设计来满足双线通讯的需求

 ros2 run turtlesim turtlesim_node

robot$ ros2 service list -t
/clear [std_srvs/srv/Empty]
/kill [turtlesim_msgs/srv/Kill]
/reset [std_srvs/srv/Empty]
/spawn [turtlesim_msgs/srv/Spawn]
/turtle1/set_pen [turtlesim_msgs/srv/SetPen]
/turtle1/teleport_absolute [turtlesim_msgs/srv/TeleportAbsolute]
/turtle1/teleport_relative [turtlesim_msgs/srv/TeleportRelative]
/turtlesim/describe_parameters [rcl_interfaces/srv/DescribeParameters]

-t 参数显示了服务的接口类型

查看详细定义
robot$ ros2 interface show turtlesim_msgs/srv/Spawn
float32 x
float32 y
float32 theta
string name # Optional.  A unique name will be created and returned if this is empty
---
string name

调用一下
```shell
ros2 service call /spawn turtlesim_msgs/srv/Spawn "{x: 2, y: 3}"
```
waiting for service to become available...
requester: making request: turtlesim_msgs.srv.Spawn_Request(x=2.0, y=3.0, theta=0.0, name='')

response:
turtlesim_msgs.srv.Spawn_Response(name='turtle2')

`ros2 service list -t | grep para`

`ros2 param list`
/turtlesim:
  background_b
  background_g
  background_r

`ros2 param describe /turtlesim background_r`
Parameter name: background_r
  Type: integer
  Description: Red channel of the background color
  Constraints:
    Min value: 0
    Max value: 255
    Step: 1

`ros2 param get /turtlesim background_r`
Integer value is: 69
`ros2 param set /turtlesim background_r 255`
Set parameter successful

`ros2 param dump /turtlesim > /tmp/turtlesim_para.yaml`
bdus@bdus-X99:~$ `cat /tmp/turtlesim_para.yaml`
/turtlesim:
  ros__parameters:
    background_b: 255
    background_g: 86
    background_r: 255
    holonomic: false
    qos_overrides:
      /parameter_events:
        publisher:
          depth: 1000
          durability: volatile
          history: keep_last
          reliability: reliable
    start_type_description_service: true
    use_sim_time: false

`ros2 run turtlesim turtlesim_node --ros-args --params-file /tmp/turtlesim_para.yaml`

# 深入服务

