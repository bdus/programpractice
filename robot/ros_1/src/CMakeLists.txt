cmake_minimum_required(VERSION 3.5)
project(ros2_node_cpp)

add_executable(ros2_node_cpp ros2_node_cpp.cpp)

# #include "rclcpp/rclcpp.hpp"
find_package(rclcpp REQUIRED)
target_include_directories(ros2_node_cpp PUBLIC ${rclcpp_INCLUDE_DIRS})

target_link_libraries(ros2_node_cpp ${rclcpp_LIBRARIES})
