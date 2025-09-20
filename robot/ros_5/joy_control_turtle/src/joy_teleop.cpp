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