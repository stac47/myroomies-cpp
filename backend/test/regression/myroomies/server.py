import subprocess
import http.client
import time
import logging

class MyRoomiesServer(object):

    def __init__(self):
        self.path = '../../myroomies-server'

    def start(self):
        cmd = []
        cmd.append(self.path)
        cmd.append("--logging-path=.")
        self.server_process = subprocess.Popen(cmd)
        logging.info("Server started [pid={}]".format(self.server_process.pid))
        self.__wait_for_connection()
        logging.info("Server ready to accept connection")

    def stop(self):
        logging.info("Server stopping...")
        self.server_process.terminate()
        logging.info("Server stopped")

    def __wait_for_connection(self):
        logging.info("Wait for server connectivity")
        conn = http.client.HTTPConnection('localhost', 8080)
        while (True):
            try:
                conn.connect()
            except:
                logging.info("Server is not ready...")
                time.sleep(1)
            else:
                conn.close()
                return

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.stop()

