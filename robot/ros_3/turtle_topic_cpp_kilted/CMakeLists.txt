cmake_minimum_required(VERSION 3.8)
project(turtle_topic_cpp_kilted)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim_msgs REQUIRED)

add_executable(turtle_circle src/turtle_circle.cpp)
add_executable(turtle_control src/turtle_control.cpp)

# ament_target_dependencies(turtle_circle rclcpp geometry_msgs) 
# ament_target_dependencies(turtle_control rclcpp geometry_msgs turtlesim_msgs) 
# ament_target_dependencies() 已经被弃用，建议用 target_link_libraries() 和现代 CMake 目标。


target_include_directories(turtle_circle PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(turtle_circle PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(turtle_control PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

target_link_libraries(
  turtle_circle
  ${rclcpp_TARGETS}
  ${geometry_msgs_TARGETS}  
)

target_link_libraries(
  turtle_control
  ${rclcpp_TARGETS}
  ${geometry_msgs_TARGETS}
  ${turtlesim_msgs_TARGETS}
)

install(TARGETS 
turtle_circle
turtle_control
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
