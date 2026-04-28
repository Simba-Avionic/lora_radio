# simple ROS2 node to test my definied msg from "lora_ros_msgs" package

from lora_ros_msgs.msg import GpsShort, LoraStatus

import rclpy
from rclpy.node import Node

# GPS message - short form
class GpsShortPublisher(Node):

    def __init__(self):
        super().__init__('gps_short_publisher')
        self.publisher_ = self.create_publisher(GpsShort, 'gps_short', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        msg = GpsShort()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.latitude_deg = 37.7749
        msg.longitude_deg = -122.4194
        msg.altitude_m = 30.0
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: {msg}')

    def destroy_node(self):
        self.get_logger().info('Destroying GPS Short Publisher')
        super().destroy_node()


# LoRa status message
class LoraStatusPublisher(Node):

    def __init__(self):
        super().__init__('lora_status_publisher')
        self.publisher_ = self.create_publisher(LoraStatus, 'lora_status', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        msg = LoraStatus()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.rssi = -70.0
        msg.noise = -100.0
        msg.snr = 30.0
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: {msg}')

    def destroy_node(self):
        self.get_logger().info('Destroying LoRa Status Publisher')
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)

    gps_short_publisher = GpsShortPublisher()
    lora_status_publisher = LoraStatusPublisher()

    # rclpy.spin(gps_short_publisher)
    rclpy.spin(lora_status_publisher)

    gps_short_publisher.destroy_node()
    lora_status_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()