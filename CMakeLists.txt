cmake_minimum_required(VERSION 3.0.2)
project(amcl_error_test_node)

find_package(catkin REQUIRED COMPONENTS
  message_filters
  roscpp
  sensor_msgs
  tf2_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES amcl_error_test_node
#  CATKIN_DEPENDS message_filters roscpp sensor_msgs tf2_ros
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(amcl_laser_test src/amcl_laser_test.cpp)
target_link_libraries(amcl_laser_test ${catkin_LIBRARIES})