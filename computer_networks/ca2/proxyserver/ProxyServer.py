import socket
import threading
import time

from Caching import Caching
from LogMan import LogMan

class ProxyServer:

    def __init__(self, config):
        self.users = config['accounting']['users']
        self.logMan = LogMan(config['logging'])
        self.cache = Caching(config['caching'], self.logMan)
        self.restriction = config['restriction']
        self.HOSTNAME = '127.0.0.1'
        self.LISTEN_QUEUE = 20
        self.MAX_REQUEST_LEN = 100000
        self.CONNECTION_TIMEOUT = 10
        self.HTTP11 = b'HTTP/1.1'
        self.HTTP10 = b'HTTP/1.0'
        self.config = config
        self.logMan.log('proxy', 'socket is creating on')
        self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.serverSocket.bind((self.HOSTNAME, config['port']))
        self.serverSocket.listen(self.LISTEN_QUEUE)

    def run(self):
        while True:
            self.logMan.log('proxy', 'accept...')
            (client_socket, client_address) = self.serverSocket.accept()
            self.logMan.log('proxy', 'connection is established')
            d = threading.Thread(
                    name=self.generate_name(client_address),
                    target=self.proxyFunction(client_socket),
                    args=(self, client_socket, client_address))
            d.setDaemon(True)
            d.start()

    def generate_name(self, client_address):
        return 'trd' + str(client_address)

    def proxyFunction(self, client_socket):
        request_bytes = client_socket.recv(self.MAX_REQUEST_LEN)
        request_bytes = self.saturate(request_bytes)
        if(self.block(request_bytes)):
            self.logMan.log('restriction', 'request blocked')
            client_socket.close()
            return
        if(self.slow(request_bytes)):
            self.logMan.log('restriction', 'sleep end')
        if(self.cache.get(request_bytes) is not None):
            self.logMan.log('cache', 'response by cache entry:' + self.cache.gen(request_bytes))
            data = self.cache.get(request_bytes)
        else:
            self.logMan.log('cache', 'response without cache:' + self.cache.gen(request_bytes))
            data = self.fetch_data_from_destination(request_bytes)
            self.logMan.log('cache', 'caching entry:' + self.cache.gen(request_bytes))
            self.cache.put(request_bytes, data)
        if data is not None:
            self.send_data_to_client(client_socket, data)
        else:
            client_socket.close()

    def send_data_to_client(self, client_socket, data):
        if(self.account_has_charge(client_socket.getpeername()[0], len(data)) is not True):
            self.logMan.log('accounting', 'account no charge')
            client_socket.close()
            return
        try:
            data.replace(self.HTTP10, self.HTTP11)
            self.logMan.log('proxy', 'data sending:' + str(len(data)))
            client_socket.sendall(data)
            self.logMan.log('proxy','data sent:' + str(data))
        except Exception as e:
            self.logMan.log('proxy', str(e))

    def fetch_data_from_destination(self, request_bytes):
        if(len(request_bytes) == 0):
            self.logMan.log('proxy', 'empty request')
            return
        (destination, port) = self.parse_req(request_bytes)
        destination_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        destination_socket.settimeout(self.CONNECTION_TIMEOUT)
        destination_socket.connect((destination, port))
        destination_socket.sendall(request_bytes)
        try:
            first_chunk = destination_socket.recv(self.MAX_REQUEST_LEN)
        except Exception as a:
            self.logMan.log('proxy', 'exception:' + str(a))
            first_chunk = b''
        data = bytearray(first_chunk)
        chunk = data
        while len(chunk) > 0:
            try:
                chunk = destination_socket.recv(self.MAX_REQUEST_LEN)
                data += bytearray(chunk)
            except Exception as e:
                self.logMan.log('proxy', str(e))
                break
        self.logMan.log('proxy', 'data received:' + str(request_bytes))
        return data

    def parse_req(self, request_bytes):
        self.logMan.log('proxy', 'request:' + str(request_bytes))
        request_arr = str(request_bytes).split('\n')
        first_line = request_arr[0]
        url = first_line.split(' ')[1]
        http_pos = url.find("://")
        if (http_pos==-1):
            temp = url
        else:
            temp = url[(http_pos+3):]

        port_pos = temp.find(":")

        webserver_pos = temp.find("/")
        if webserver_pos == -1:
            webserver_pos = len(temp)

        if (port_pos == -1 or webserver_pos < port_pos):
            port = 80
            webserver = temp[:webserver_pos]
        else:
            port = int((temp[(port_pos+1):])[:webserver_pos-port_pos-1])
            webserver = temp[:port_pos]

        self.logMan.log('proxy', 'url:' + str(webserver) + '\tport:' + str(port))
        return (webserver, port)

    def saturate(self, request_bytes):
        request_bytes = request_bytes.replace(self.HTTP11, self.HTTP10)
        request_bytes = request_bytes.replace(b'Connection: keep-alive', b'Connection: close')
        request_arr = request_bytes.decode(errors='ignore').split('\n')
        i = 0
        while i < len(request_arr):
            line = request_arr[i]
            if 'Accept-Encoding' in line:
                request_arr.remove(line)
            if self.config['privacy']['enable']:
                if 'User-Agent' in line:
                    self.agent = line
                    request_arr.remove(line)
                    new_line = 'User-Agent: ' + self.config['privacy']['userAgent'] + '\r'
                    request_arr.insert(i, new_line)
            i += 1

        request_bytes = str.encode('\n'.join(request_arr))
        return request_bytes

    def block(self, request_bytes):
        if(self.restriction['enable'] is not True):
            return False
        targets = self.restriction['targets']
        for target in targets:
            if(target['URL'] in str(request_bytes)):
                if(target['type'] == 'BLOCK'):
                    return True
        return False

    def slow(self, request_bytes):
        if(self.restriction['enable'] is not True):
            return False
        targets = self.restriction['targets']
        for target in targets:
            if(target['URL'] in str(request_bytes)):
                if(target['type'] == 'SLOW'):
                    delay = int(target['delay'])/1000
                    self.logMan.log('restriction', 'request slowed for: ' + str(delay) + ' sec')
                    time.sleep(delay)
                    return True
        return False

    def account_has_charge(self, client_ip, data_amount):
        for user in self.users:
            if user['IP'] == client_ip:
                volume = int(user['volume'])
                if(volume < data_amount):
                    return False
                volume -= data_amount
                user['volume'] = str(volume)
                self.logMan.log('accounting', 'user: '+ client_ip + ' discharging:' + str(data_amount) + ' new volume' + user['volume'])
                return volume > 0
        return True