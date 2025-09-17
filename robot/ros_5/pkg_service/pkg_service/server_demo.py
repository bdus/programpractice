import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class Service_server(Node):
    def __init__(self, name):
        super().__init__(name)
        self.srv = self.create_service(AddTwoInts, '/add_two_ints', self.add2Ints_callback)
    
    def add2Ints_callback(self, request, response):
        response.sum = request.a + request.b
        print("response.sum = ", response.sum)
        return response        

def main():
    rclpy.init()
    server_demo = Service_server("publisher_node")
    rclpy.spin(server_demo)
    server_demo.destroy_node()
    rclpy.shutdown()
    

if __name__ == '__main__':
    main()
