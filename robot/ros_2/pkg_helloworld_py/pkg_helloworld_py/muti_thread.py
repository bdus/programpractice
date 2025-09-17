import threading
import requests

from pkg_helloworld_py.helloworld import HelloWorldNode


class Explorer(HelloWorldNode):
    def __init__(self, name):        
        self.name = name

    def explore(self, url, callback):
        print(f"Thread: {threading.get_ident()} downloading: {url}")
        response = requests.get(url)
        response.encoding = 'utf-8'
        callback(url, self.name, response.text)
    
    def start_explore(self, url, callback):
        thread = threading.Thread(target=self.explore, args=(url, callback))
        thread.start()


def post_explore_print(url, name, place):
    print(f'loaded {url}, {name} exploring {place}.')


def main():
    explore = Explorer('bajieZhu')
    explore.start_explore("http://localhost:8000/place1.txt", post_explore_print)
    explore.start_explore("http://localhost:8000/place2.txt", post_explore_print)
    explore.start_explore("http://localhost:8000/place3.txt", post_explore_print)
