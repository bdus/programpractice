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

