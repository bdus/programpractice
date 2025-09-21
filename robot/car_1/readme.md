ahboom@yahboom-VM:~$ ros2 node info /YB_Car_Node 
```bash
/YB_Car_Node
  Subscribers:
    /beep: std_msgs/msg/UInt16
    /cmd_vel: geometry_msgs/msg/Twist
    /servo_s1: std_msgs/msg/Int32
    /servo_s2: std_msgs/msg/Int32
  Publishers:
    /battery: std_msgs/msg/UInt16
    /imu: sensor_msgs/msg/Imu
    /odom_raw: nav_msgs/msg/Odometry
    /scan: sensor_msgs/msg/LaserScan
  Service Servers:
```

ros2 topic list 
```bash
/battery
/beep
/cmd_vel
/imu
/odom_raw
/parameter_events
/rosout
/scan
/servo_s1
/servo_s2
```

yahboom@yahboom-VM:~$ ros2 topic info /scan 
```bash
Type: sensor_msgs/msg/LaserScan
Publisher count: 1
Subscription count: 0
```

```bash
yahboom@yahboom-VM:~$ ros2 interface show sensor_msgs/msg/LaserScan 
# Single scan from a planar laser range-finder
#
# If you have another ranging device with different behavior (e.g. a sonar
# array), please find or create a different message, since applications
# will make fairly laser-specific assumptions about this data

std_msgs/Header header # timestamp in the header is the acquisition time of
	builtin_interfaces/Time stamp
		int32 sec
		uint32 nanosec
	string frame_id
                             # the first ray in the scan.
                             #
                             # in frame frame_id, angles are measured around
                             # the positive Z axis (counterclockwise, if Z is up)
                             # with zero angle being forward along the x axis

float32 angle_min            # start angle of the scan [rad]
float32 angle_max            # end angle of the scan [rad]
float32 angle_increment      # angular distance between measurements [rad]

float32 time_increment       # time between measurements [seconds] - if your scanner
                             # is moving, this will be used in interpolating position
                             # of 3d points
float32 scan_time            # time between scans [seconds]

float32 range_min            # minimum range value [m]
float32 range_max            # maximum range value [m]

float32[] ranges             # range data [m]
                             # (Note: values < range_min or > range_max should be discarded)
float32[] intensities        # intensity data [device-specific units].  If your
                             # device does not provide intensities, please leave
                             # the array empty.
yahboom@yahboom-VM:~$ 
```

```bash
yahboom@yahboom-VM:~$ ros2 topic info /odom_raw
Type: nav_msgs/msg/Odometry
Publisher count: 1
Subscription count: 0

yahboom@yahboom-VM:~$ ros2 interface show nav_msgs/msg/Odometry 
# This represents an estimate of a position and velocity in free space.
# The pose in this message should be specified in the coordinate frame given by header.frame_id
# The twist in this message should be specified in the coordinate frame given by the child_frame_id

# Includes the frame id of the pose parent.
std_msgs/Header header
	builtin_interfaces/Time stamp
		int32 sec
		uint32 nanosec
	string frame_id

# Frame id the pose points to. The twist is in this coordinate frame.
string child_frame_id

# Estimated pose that is typically relative to a fixed world frame.
geometry_msgs/PoseWithCovariance pose
	Pose pose
		Point position
			float64 x
			float64 y
			float64 z
		Quaternion orientation
			float64 x 0
			float64 y 0
			float64 z 0
			float64 w 1
	float64[36] covariance

# Estimated linear and angular velocity relative to child_frame_id.
geometry_msgs/TwistWithCovariance twist
	Twist twist
		Vector3  linear
			float64 x
			float64 y
			float64 z
		Vector3  angular
			float64 x
			float64 y
			float64 z
	float64[36] covariance

```

# 在linux上连接小车



```bash
# 首先在虚拟机环境中配置 ubuntu的ip等 正确

# 然后登录 ubuntu
export ROS_DOMAIN_ID=20
# sudo ufw allow 8090/udp # 可能需要放通防火墙

# 启动网关
docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:humble udp4 --port 8090 -v4

# 启动小车 网关连接成功
```

这时候直接在ubuntu执行 ros2 node list 是找不到节点的

两种方式
第一种
```bash
bdus@bdus-X99:~$ docker ps
CONTAINER ID   IMAGE                             COMMAND                  CREA
TED         STATUS         PORTS     NAMES
fbe9e808a5e7   microros/micro-ros-agent:humble   "/bin/sh /micro-ros_…"   6 mi
nutes ago   Up 6 minutes             angry_hoover
bdus@bdus-X99:~$ docker exec -it fbe9e808a5e7 /bin/bash
root@bdus-X99:/uros_ws# ros2 node list
root@bdus-X99:/uros_ws# source /opt/ros/humble/setup.bash
root@bdus-X99:/uros_ws# ros2 node list
root@bdus-X99:/uros_ws# echo $ROS_DOMAIN_ID

root@bdus-X99:/uros_ws# export ROS_DOMAIN_ID=20
root@bdus-X99:/uros_ws# source /opt/ros/humble/setup.bash
root@bdus-X99:/uros_ws# ros2 node list
/YB_Car_Node

```
第二种

```bash
bdus@bdus-X99:~$ export ROS_DOMAIN_ID=20
bdus@bdus-X99:~$ ros2 node list
/YB_Car_Node
```


https://micro.ros.org/