#!/user/bin/env python
# -*- coding:utf-8 -*-

import rclpy
from rclpy.node import Node

def main():
    rclpy.init()
    node = Node("python_node")
    node.get_logger().info('hi from python ros node.')
    rclpy.spin(node)
    rclpy.shutdown()

if __name__=="__main__":
    main()