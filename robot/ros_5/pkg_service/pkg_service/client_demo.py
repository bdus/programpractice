import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class Service_Client(Node):
    def __init__(self, name):
        super().__init__(name)
        self.client = self.create_client(AddTwoInts, '/add_two_ints')
        while not self.client.wait_for_service(timeout_sec=1.0):
            print("Service not available, waiting again...")

        self.request = AddTwoInts.Request()
    
    def send_request(self):
        self.request.a = 10
        self.request.b = 90
        #发送服务请求
        self.future = self.client.call_async(self.request)


def main():
    rclpy.init()
    service_client = Service_Client("client_node")
    service_client.send_request()
    while rclpy.ok():
        rclpy.spin_once(service_client)
        if service_client.future.done():
            try:
                response = service_client.future.result()
                print("service_client.request.a = ", service_client.request.a)
                print("service_client.request.b = ", service_client.request.b)
                print("Result = ", response.sum)
            except Exception as e:
                service_client.get_logger().info("service call failed %r" % (e,))
        break

    service_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
