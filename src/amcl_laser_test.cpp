#include "ros/ros.h"

#include "message_filters/subscriber.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#include <sensor_msgs/LaserScan.h>

class LaserTest {
public:
  LaserTest() {
    std::string scan_topic_;
    nh_.param<std::string>("scan", scan_topic_, "/front/scan");
    std::string odom_frame_id_;
    nh_.param<std::string>("odom_frame_id", odom_frame_id_, "/odom");
    
    tf_.reset(new tf2_ros::Buffer());
    tfl_.reset(new tf2_ros::TransformListener(*tf_));

    laser_scan_sub_ = new message_filters::Subscriber<sensor_msgs::LaserScan>(
        nh_, scan_topic_, 100);
    laser_scan_filter_ = new tf2_ros::MessageFilter<sensor_msgs::LaserScan>(
        *laser_scan_sub_, *tf_, odom_frame_id_, 100, nh_);

    laser_scan_filter_->registerCallback(
        boost::bind(&LaserTest::laserReceived, this, _1));
    laser_scan_filter_->registerFailureCallback(
        boost::bind(&LaserTest::laserFailed, this, _1, _2));
  }

  void laserReceived(const sensor_msgs::LaserScanConstPtr &laser_scan) {
    ROS_INFO("got laser");
  }

  void laserFailed(const sensor_msgs::LaserScan::ConstPtr &message,
                   tf2_ros::FilterFailureReason reason) {
    if (reason == tf2_ros::FilterFailureReason::EmptyFrameID) {
      ROS_INFO("Failed to get laser: The frame_id on the message is empty.");
    } else if (reason == tf2_ros::FilterFailureReason::OutTheBack) {
      ROS_INFO(
          "Failed to get laser: The timestamp on the message is more than the "
          "cache length earlier than the newest data in the transform cache.");
    } else {
      ROS_INFO("Failed to get laser: unknown reason");
    }
  }

private:
  std::shared_ptr<tf2_ros::Buffer> tf_;
  std::shared_ptr<tf2_ros::TransformListener> tfl_;

  std::string target_frame_;
  ros::NodeHandle nh_;
  message_filters::Subscriber<sensor_msgs::LaserScan> *laser_scan_sub_;
  tf2_ros::MessageFilter<sensor_msgs::LaserScan> *laser_scan_filter_;
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "amcl_laser_test");
  LaserTest lt;
  ros::spin();
  return 0;
};