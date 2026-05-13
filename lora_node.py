# simple ROS2 node to test my definied msg from "lora_ros_msgs" package

from lora_ros_msgs.msg import GpsShort, LoraStatus, LoraGnss

# import threads
import threading

# import mavlink (simba_mavlink dialect)

from pymavlink import mavutil
import simba_mavlink
mavutil.mavlink = simba_mavlink

import rclpy
from rclpy.node import Node

# GPS message - short form
class LoRaNode(Node):

    def __init__(self):
        super().__init__('lora_node')
        self.publisher_lora_gps = self.create_publisher(GpsShort, '/rocket/lora/gps', 10)
        self.publisher_rocket_gps = self.create_publisher(GpsShort, '/rocket/gps', 10)
        self.publisher_lora_status = self.create_publisher(LoraStatus, '/mission_control/lora/status', 10)
        self.publisher_lora_gnss = self.create_publisher(LoraGnss, '/mission_control/lora/gnss', 10)
        self.mavlink_connection = mavutil.mavlink_connection('/dev/ttyACM0', baud=57600)

        self.r_thread = threading.Thread(target=self.reading_thread)
        self.working = True
        self.r_thread.start()


    def reading_thread(self):
        while self.working:
            msg = self.mavlink_connection.recv_match(blocking=True)
            if msg is not None:
                if msg.get_type() == 'L76K_GPS':
                    print(msg)
                    ros_msg = LoraGnss()
                    ros_msg.header.stamp = self.get_clock().now().to_msg()
                    ros_msg.header.frame_id = '/mission_control/lora'
                    ros_msg.date = msg.date
                    ros_msg.time = msg.time
                    ros_msg.latitude_deg = msg.lat / 1e7
                    ros_msg.longitude_deg = msg.lon / 1e7
                    ros_msg.altitude_m = msg.alt / 1e3
                    ros_msg.speed_mps = msg.speed
                    ros_msg.course_deg = msg.course
                    ros_msg.satellites_visible = msg.satellites_visible
                    ros_msg.hdop = msg.hdop / 1e2
                    ros_msg.sentences_with_fix = msg.sentences_with_fix
                    self.publisher_lora_gnss.publish(ros_msg)
                    self.get_logger().info(f'Published LoRa GNSS: {ros_msg}')
                elif msg.get_type() == 'RADIO_STATUS':
                    print(msg)
                    ros_msg = LoraStatus()
                    ros_msg.header.stamp = self.get_clock().now().to_msg()
                    ros_msg.header.frame_id = '/mission_control/lora'
                    ros_msg.rssi = float(msg.rssi) - 200
                    ros_msg.noise = float(msg.noise) - 200
                    ros_msg.snr = float(msg.rssi) - float(msg.noise)
                    ros_msg.tx_buff = msg.txbuf
                    ros_msg.rem_rssi = float(msg.remrssi) - 200
                    ros_msg.rem_noise = float(msg.remnoise) - 200
                    ros_msg.rem_snr = float(msg.remrssi) - float(msg.remnoise)
                    ros_msg.rx_errors = msg.rxerrors
                    ros_msg.rx_fixed = msg.fixed
                    self.publisher_lora_status.publish(ros_msg)
                    self.get_logger().info(f'Published LoRa Status: {ros_msg}')
                elif msg.get_type() == 'SIMBA_GPS':
                    print(msg)
                    ros_msg = GpsShort()
                    ros_msg.header.stamp = self.get_clock().now().to_msg()
                    ros_msg.latitude_deg = msg.lat / 1e7
                    ros_msg.longitude_deg = msg.lon / 1e7
                    ros_msg.altitude_m = msg.altitude / 1e3

                    if msg.get_srcComponent() == 221: # GPS from lora
                        ros_msg.header.frame_id = '/rocket/lora'
                        self.publisher_lora_gps.publish(ros_msg)
                    elif msg.get_srcComponent() == 200: # GPS from rocket GNSS
                        ros_msg.header.frame_id = '/rocket/gps'
                        self.publisher_rocket_gps.publish(ros_msg)

                    self.get_logger().info(f'Published GPS: {ros_msg}')
                

    def destroy_node(self):
        self.get_logger().info('Destroying GPS Short Publisher')
        self.working = False
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)

    lora_node = LoRaNode()
    rclpy.spin(lora_node)
    lora_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()