import subprocess
import time
import base64
import json
import http.client

import logging
logging.basicConfig(
    format='%(asctime)s [%(levelname)s] %(message)s',
    filename='regression.log',
    level=logging.DEBUG)

from . import tools
from . import models
from .client import MyRoomiesClient


class MyRoomiesServer(object):

    def __init__(self):
        self.path = '../../myroomies-server-gnu'
        self.already_started = False

    def start(self):
        cmd = []
        cmd.append(self.path)
        cmd.append("--logging-path=.")
        self.already_started = self.__wait_for_connection(1)
        if self.already_started:
            logging.info("Server has ready been started")
        else:
            self.server_process = subprocess.Popen(cmd)
            logging.info("Server started [pid={}]".format(self.server_process.pid))
            self.__wait_for_connection()
        logging.info("Server ready to accept connection")

    def stop(self):
        if (not self.already_started):
            logging.info("Server stopping...")
            self.server_process.terminate()
            logging.info("Server stopped")
        else:
            logging.info("Not stopping the server")

    def __wait_for_connection(self, max_try=-1):
        logging.info("Wait for server connectivity")
        conn = http.client.HTTPConnection('localhost', 8080)
        while (max_try == -1 or max_try > 0):
            try:
                if max_try > 0:
                    max_try -= 1
                conn.connect()
            except:
                logging.info("Server is not ready...")
                time.sleep(1)
            else:
                conn.close()
                return True
        return False

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.stop()

def create_houseshare(roomies_nb):
    """ Push a houseshare and related roomies to the server. Returns a 2-uple
    whose first element is the created houseshare id and the second a list of
    created users belonging to this houseshare)
    """

    field = "h{}_{}{}"
    houseshare_id = 1
    roomies = []
    client = MyRoomiesClient('localhost', 8080)
    for i in range(roomies_nb):
        u = models.User()
        u.login = field.format(houseshare_id, "login", i)
        u.houseshare_id = houseshare_id
        password = field.format(houseshare_id, "password", i)
        u.password = password
        u.firstname = field.format(houseshare_id, "firstname", i)
        u.lastname = field.format(houseshare_id, "lastname", i)
        u.email = field.format(houseshare_id, "email", i) + "@host.com"
        u.date_of_birth = "19810619"
        user_str = json.dumps(u, cls=models.UserEncoder)
        headers = {}
        tools.add_admin_authorization_header(headers)
        status, data = client.request('POST', '/users', user_str, headers=headers)
        u = json.loads(data, object_hook=models.User.from_json)
        u.password = password
        roomies.append(u)
    client.close()
    return (houseshare_id, roomies)
