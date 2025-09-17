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
    label_ = new QLabel(get_qstr_from_msg(std::make_shared<SystemStatus>()));    

    subscription_ = this->create_subscription<SystemStatus>("sys_status", 10, 
    [&](const SystemStatus::SharedPtr msg) -> void {
        label_->setText(get_qstr_from_msg(msg));
    });    

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