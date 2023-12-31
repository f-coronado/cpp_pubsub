// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicables law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
* @file subscriber_member_function.cpp
* @author f-coronado
* @brief Subscriber script
* @date 11/20/2023
*
* @copyright Copyright (c) 2023
*
*/

#include <functional>
#include <memory>
#include <cpp_pubsub/srv/speak.hpp>
#include <std_msgs/msg/string.hpp>

#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
 public:
  /**
   * @brief MinimalSubscriber node created to listen to talker/publisher
   *
   */
  MinimalSubscriber()
  : Node("minimal_subscriber") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

 private:
  /**
   * @brief calls the topic and retrieves the message
   *
   * @param msg
   */
  void topic_callback(const std_msgs::msg::String & msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
