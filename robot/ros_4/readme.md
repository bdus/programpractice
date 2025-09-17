
# 系统实时状态发布和显示的小工具


首先实现自定义的通信接口的数据结构
实现一个python的 publisher发布topic /sys_status 然后Qt 节点订阅topic 显示数据

## 实现自定义的通信接口的数据结构

ros2 pkg create status_interfaces --build-type ament_cmake --dependencies rosidl_default_generators builtin_interfaces --license Apache-2.0

mkdir -p status_interfaces/msg/
touch status_interfaces/msg/SystemStatus.msg
```
builtin_interfaces/Time stamp   # 记录时间戳  引用buildin_interfaces数据结构
string host_name                # 系统名称
float32 cpu_percent             # CPU 使用率
float32 memory_percent          # 内存使用率
float32 memory_total            # 内存总量
float32 memory_available        # 剩余有效内存
float64 net_send                # 网络发送数据总量
float64 net_recv                # 网络接受数据总量
```

### edited
status_interfaces/CMakeLists.txt
```
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SystemStatus.msg"
  DEPENDENCIES builtin_interfaces
)
```
status_interfaces/package.xml
```
  <license>Apache-2.0</license>

  <member_of_group>rosidl_interface_packages</member_of_group>
  <buildtool_depend>ament_cmake</buildtool_depend>
```

yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ source install/setup.bash 
yahboom@yahboom-VM:~/a_linux_img/practice/ros_4$ ros2 interface show status_interfaces/msg/SystemStatus 
builtin_interfaces/Time stamp   # 记录时间戳  引用 builtin_interfaces 数据结构
	int32 sec
	uint32 nanosec
string host_name                # 系统名称
float32 cpu_percent             # CPU 使用率
float32 memory_percent          # 内存使用率
float32 memory_total            # 内存总量
float32 memory_available        # 剩余有效内存
float64 net_send                # 网络发送数据总量
float64 net_recv                # 网络接受数据总量

## 实现一个python的 publisher发布topic /sys_status

ros2 pkg create status_publisher --build-type ament_python --dependencies rclpy status_interfaces --license Apache-2.0 --node-name sys_status_pub

```python
import rclpy
from rclpy.node import Node
from status_interfaces.msg import SystemStatus
import psutil
import platform

class SysStatusPub(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.status_publisher_ = self.create_publisher(SystemStatus, 'sys_status', 10)
        self.timer = self.create_timer(1, self.timer_callback)
    
    def timer_callback(self):
        cpu_percent = psutil.cpu_percent()
        memory_info = psutil.virtual_memory()
        net_io_counters = psutil.net_io_counters()

        msg = SystemStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.host_name = platform.node()
        msg.cpu_percent = cpu_percent
        msg.memory_percent = memory_info.percent
        msg.memory_total = memory_info.total / 1024 / 1024
        msg.memory_available = memory_info.available / 1024 / 1024
        msg.net_send = net_io_counters.bytes_sent / 1024 / 1024
        msg.net_recv = net_io_counters.bytes_recv / 1024 / 1024

        self.get_logger().info(f'publish:{str(msg)}')
        self.status_publisher_.publish(msg)

def main():
    rclpy.init()
    node = SysStatusPub('sys_status_pub')
    rclpy.spin(node)
    rclpy.shutdown()

```


## display with Qt

ros2 pkg create status_display --build-type ament_cmake --dependencies rclcpp status_interfaces --license Apache-2.0 --node-name hello_qt

```cpp

#include <QApplication>
#include <QLabel>
#include <QString>


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QLabel* lable  = new QLabel();
    QString message = QString：：fromStdString("Hello Qt");
    lable->setText(message);
    lable->show();
    app.exec();
    
    return 0;
}

```

```
find_package(status_interfaces REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(hello_qt src/hello_qt.cpp)

target_link_libraries(hello_qt Qt5::Widgets)

target_include_directories(hello_qt PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  DESTINATION lib/${PROJECT_NAME}
)


```

sys_status_display.cpp
```cpp
#include <QApplication>
#include <QLabel>
#include <QString>
#include "rclcpp/rclcpp.hpp"
#include "status_interfaces/msg/system_status.hpp"

using SystemStatus = status_interfaces::msg::SystemStatus;

class SysStatusDisplay : public rclcpp::Node 
{
public:
    SysStatusDisplay();
    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg);

private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscription_;
    QLabel* label_;    
};

SysStatusDisplay::SysStatusDisplay() : Node("sys_status_display")
{
    subscription_ = this->create_subscription<SystemStatus>("sys_status", 10, 
    [&](const SystemStatus::SharedPtr msg) -> void {
        label_-> setText(get_qstr_from_msg(msg));
    });

    label_ = new QLabel(get_qstr_from_msg(std::make_shared<SystemStatus>() ));
    label_->show();
}

QString SysStatusDisplay::get_qstr_from_msg(const SystemStatus::SharedPtr msg) 
{
    std::stringstream show_str;
    show_str
        << "============ 系统状态可视化显示工具 ============\n"
        << "数据时间：\t\t" << msg->stamp.sec << "\ts\n"
        << "用户名：\t\t"   << msg->host_name << "\t\n"
        << "CPU使用率\t\t"  << msg->cpu_percent << "\t%\n"
        << "内存使用率\t\t"  << msg->memory_percent << "\t%\n"
        << "内存总大小\t\t"  << msg->memory_total << "\tMB\n"
        << "剩余有效内存\t\t"  << msg->memory_available << "\tMB\n"
        << "网络发送量\t\t"  << msg->net_send << "\tMB\n"
        << "网络接受量\t\t"  << msg->net_recv << "\tMB\n"
        << "===============================================";
           
    return QString::fromStdString(show_str.str());
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<SysStatusDisplay>();
    std::thread spin_thread([&]() -> void { rclcpp::spin(node); });
    spin_thread.detach();
    
    app.exec();
    rclcpp::shutdown();

    return 0;
}

```


source install/setup.bash 
ros2 run status_publisher sys_status_pub
ros2 run status_display sys_status_display 