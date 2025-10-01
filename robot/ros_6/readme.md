# 仿真

https://www.yahboom.com/build.html?id=8718&cid=626
https://turtlebot.github.io/turtlebot4-user-manual/software/turtlebot4_simulator.html#installation


安装tutlebot3模拟器功能包
sudo apt install ros-${ROS_DISTRO}-turtlebot3*
安装ros和gazebo桥接工具
sudo apt install ros-${ROS_DISTRO}-ros-gz
设置turtlebot3机器人类型环境变量
export TURTLEBOT3_MODEL=waffle
启动gazebo仿真环境
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py

# build a simi-car

sudo apt install ros-humble-gazebo-ros-pkgs
sudo apt install ros-humble-gazebo-ros2-control

ros2 pkg create carbot_description --build-type ament_cmake --license Apache-2.0

ros2 launch carbot_description display_robot.launch.py model:=./carbot_description/urdf/carbot/carbot.urdf.xacro

source /usr/share/gazebo/setup.bash
ros2 launch carbot_description gazebo_sim.launch.py
