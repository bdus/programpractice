import rclpy
from rclpy.node import Node
import time


class HelloWorldNode(Node):
    def __init__(self, name):        
        super().__init__(name)
        self.name = name
        hi_count = 3
        while rclpy.ok() and hi_count > 0:
            self.get_logger().info("Hello World") # ROS2日志输出
            time.sleep(0.5)
            hi_count -= 1
    
    def say_hi_to(self, identity: str):
        self.get_logger().info("Hi {0}, I'm {1}.".format(identity, self.name))       


def main(args=None):
    rclpy.init(args=args)
    node = HelloWorldNode("helloworld")
    node.say_hi_to('bdus')
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
