import hashlib
import time


class Caching:

    def __init__(self, config, logMan):
        self.keys = list()
        self.logMan = logMan
        self.cache = dict()
        self.disable = not config['enable']
        self.size = config['size']

    def put(self, request, val):
        if(self.disable or str(request).find('no-cache') is not -1):
            self.logMan.log('cache', 'caching forbidden')
            return
        if(len(self.cache) == self.size):
            self.logMan.log('cache', 'cache is full, remove oldest')
            self.cache.pop(self.keys[0])
            self.keys.pop(0)

        key = self.gen(request)
        self.cache[key] = val
        if(key in self.keys):
            self.keys.remove(key)
        self.keys.append(key)

    def get(self, requset):
        if(self.disable):
            return None
        self.logMan.log('cache', 'read cache successful, max:' + str(self.size) + ', actual:' + str(len(self.keys)) + ',' + str(len(self.cache)))
        key = self.gen(requset)
        if(key in self.keys):
            self.keys.remove(key)
            self.keys.append(key)
        data = self.cache.get(key)
        if(self.valid(data)):
            return data
        else:
            self.logMan.log('expired cache detected')
            self.keys.remove(key)
            self.cache.pop(key)
            return None

    def gen(self, request_bytes):
        key = ''
        request_arr = request_bytes.decode(errors='ignore').split('\n')
        for line in request_arr:
            if(line.find('GET ') is not -1 or line.find("Cookie: ") is not -1):
                key += line
        return hashlib.md5(key.encode()).hexdigest()

    def valid(self, response):
        try:
            res_arr = response.decode(errors='ignore').split('\n')
            for line in res_arr:
                if(line.find('Expires: ') is not -1):
                    timestamp = line.replace('Expires: ', '')
                    exp = time.strptime(timestamp, '%a, %d %b %Y %H:%M:%S GMT')
                    if(time.now() > exp):
                        return False
            return True
        finally:
            return True
