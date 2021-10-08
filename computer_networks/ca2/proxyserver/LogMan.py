import logging

class LogMan:
    def __init__(self, config):
        self.enable = config['enable']
        self.logFile = config['logFile']

    def log(self, label, info):
        if self.enable is False:
            pass
        logging.basicConfig(filename=self.logFile, filemode='w', format='[%(asctime)s]\t%(message)s', level=logging.INFO)
        message = '(' + label + ')\t' + info;
        logging.info(message)
        print(info)