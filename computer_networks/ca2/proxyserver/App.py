from ProxyServer import ProxyServer
import json


class App(object):

    def read_config(self):
        with open('config.json') as json_file:
            self.config = json.load(json_file)
        print('config read:', str(self.config))

    def main(self):
        self.read_config();
        server = ProxyServer(self.config)
        server.run()
