cmake_minimum_required(VERSION 3.8)
project(lora_ros_msgs)

# Set paths to msg and srv directories
set(MSG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/msg")

# Find all message files in msg directory
file(GLOB_RECURSE MSG_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${MSG_DIR}/*.msg")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${MSG_FILES}

  DEPENDENCIES builtin_interfaces std_msgs
)

ament_package()
