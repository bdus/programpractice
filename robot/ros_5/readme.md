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

# 实现一个基于手柄控制乌龟运动的Node


根据ros版本选择joy驱动
```
sudo apt-get install ros-kilted-joy-linux
```

插入手柄观察新增设备 js0

```
bdus@bdus-X99:~$ ls /dev/input/
event0  event1  event10  event2  event3  event4  event5  event6  event7  event8  event9  mice
bdus@bdus-X99:~$ ls /dev/input/
by-id    event0  event10  event2  event4  event6  event8  js0
by-path  event1  event11  event3  event5  event7  event9  mice
```

ls -l /dev/input/js0  # 查看当前权限
如果权限不足（无rw），临时更改：

bash
sudo chmod a+rw /dev/input/js0
注意：这种方式在重启后可能失效。若要永久解决，可以创建UDEV规则


配置好权限后，可以启动ROS2节点来测试手柄。

启动joy节点：

```bash
ros2 run joy joy_node
```

bdus@bdus-X99:~$ ros2 node list
```bash
/joy_node
```

ros2 node info /joy_node
```bash
/joy_node
  Subscribers:
    /joy/set_feedback: sensor_msgs/msg/JoyFeedback
  Publishers:
    /joy: sensor_msgs/msg/Joy
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /rosout: rcl_interfaces/msg/Log
  Service Servers:
    /joy_node/describe_parameters: rcl_interfaces/srv/DescribeParameters
    /joy_node/get_parameter_types: rcl
    ...
```    

ros2 topic info /joy
```bash
Type: sensor_msgs/msg/Joy
Publisher count: 1
Subscription count: 0  
```

bdus@bdus-X99:~$ ros2 interface show sensor_msgs/msg/Joy
```bash
# Reports the state of a joystick's axes and buttons.

# The timestamp is the time at which data is received from the joystick.
std_msgs/Header header
        builtin_interfaces/Time stamp
                int32 sec
                uint32 nanosec
        string frame_id

# The axes measurements from a joystick.
float32[] axes

# The buttons measurements from a joystick.
int32[] buttons
```

ros2 topic echo /joy

ros2 run turtlesim turtlesim_node

ros2 pkg create joy_control_turtle --build-type ament_cmake --dependencies rclcpp sensor_msgs geometry_msgs joy turtlesim --node-name joy_teleop

编写节点代码：
在 joy_teleop/src 目录下创建 joy_teleop.cpp 文件，并输入以下代码。这个节点订阅了 /joy 话题，将手柄输入转换为乌龟的线速度和角速度，并发布到 /turtle1/cmd_vel 话题

先把 [画圆圈的代码拷贝过来](../ros_3/turtle_topic_cpp/src/turtle_circle.cpp)


colcon build --packages-select joy_control_turtle
source install/setup.bash
ros2 run joy_control_turtle joy_teleop


```cpp
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist.hpp>


using namespace std::chrono_literals;

class TurtleCircle : public rclcpp::Node
{
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    void timer_callback();

public:
    explicit TurtleCircle(const std::string & node_name); // explicit c++关键字，避免类型隐式转换

};

TurtleCircle::TurtleCircle(const std::string & node_name) : Node(node_name) 
{
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(100ms, std::bind(&TurtleCircle::timer_callback, this));
}

void TurtleCircle::timer_callback()
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = 1.0;
    msg.angular.z = 0.5;
    publisher_->publish(msg);
}



class JoyTeleop : public rclcpp::Node
{
private:    
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_turtle_;

    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
public:
    explicit JoyTeleop(const std::string & node_name); // explicit c++关键字

private:
    int axis_linear_;
    int axis_angular_;
    double scale_linear_;
    double scale_angular_;
    double deadzone_;
};

JoyTeleop::JoyTeleop(const std::string & node_name) : Node(node_name),
    axis_linear_(1), axis_angular_(0), scale_linear_(5.0), scale_angular_(5.0), deadzone_(0.05)
{
    // 参数：可配置映射和缩放因子
    this->declare_parameter("axis_linear", this->axis_linear_);   // 通常左摇杆上下控制前后
    this->declare_parameter("axis_angular", this->axis_angular_);  // 通常左摇杆左右控制转向
    this->declare_parameter("scale_linear", this->scale_linear_); // 线速度缩放因子
    this->declare_parameter("scale_angular", this->scale_angular_); // 角速度缩放因子
    this->declare_parameter("deadzone", this->deadzone_);    // 死区阈值，防止摇杆轻微漂移

    // 从参数服务器获取参数
    axis_linear_ = this->get_parameter("axis_linear").as_int();
    axis_angular_ = this->get_parameter("axis_angular").as_int();
    scale_linear_ = this->get_parameter("scale_linear").as_double();
    scale_angular_ = this->get_parameter("scale_angular").as_double();
    deadzone_ = this->get_parameter("deadzone").as_double();

    
    pub_turtle_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);    
    sub_joy_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "/joy", 10, std::bind(&JoyTeleop::joy_callback, this, std::placeholders::_1));
    
    RCLCPP_INFO(this->get_logger(), "JoyTeleop node has been initialized.");
    RCLCPP_INFO(this->get_logger(), "Linear axis: %d, Angular axis: %d", axis_linear_, axis_angular_);
}


void JoyTeleop::joy_callback(const sensor_msgs::msg::Joy::SharedPtr joy_msg)
{
    auto twist = geometry_msgs::msg::Twist();

    // 应用死区处理：如果摇杆偏移量小于死区阈值，则视为零
    double linear_input = joy_msg->axes[axis_linear_];
    double angular_input = joy_msg->axes[axis_angular_];

    // 应用死区
    if (std::abs(linear_input) < deadzone_) {
        linear_input = 0.0;
    }
    if (std::abs(angular_input) < deadzone_) {
        angular_input = 0.0;
    }

    twist.linear.x = linear_input * scale_linear_;
    twist.angular.z = angular_input * scale_angular_;

    pub_turtle_->publish(twist);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    // auto node = std::make_shared<TurtleCircle>("turtle_square");
    auto node = std::make_shared<JoyTeleop>("joy_teleop");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
```