#!/usr/bin/env python3
# vi:set fileencoding=utf-8 :

"""
Created on 2016-01-14

@author : Laurent Stacul
"""

import subprocess
import http.client
import time
import json

class MyRoomiesServer(object):

    def __init__(self, path_to_bin):
        self.path = path_to_bin

    def start(self):
        self.server_process = subprocess.Popen(self.path)
        print("Server started [pid={}]".format(self.server_process.pid))
        self.__wait_for_connection()
        print("Server ready to accept connection")


    def stop(self):
        self.server_process.kill()
        print("Server stopped")

    def __wait_for_connection(self):
        print("Wait for server connectivity")
        conn = http.client.HTTPConnection('localhost', 8080)
        while (True):
            try:
                conn.connect()
            except:
                print("Server is not ready...")
                time.sleep(1)
            else:
                conn.close()
                return

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.stop()

if __name__ == '__main__':
    with MyRoomiesServer('./myroomies-server') as server:
        conn = http.client.HTTPConnection('localhost', 8080)
        conn.request('GET', '/money')
        response = conn.getresponse()
        data = response.read()
        print("Status {}: {}".format(response.status, data))
        headers = {}
        headers['Authorization'] =  'Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='
        conn.request('GET', '/money', headers=headers)
        response = conn.getresponse()
        data = response.read()
        print("Status {}: {}".format(response.status, data))
        expenses = json.loads(str(data, 'utf-8'))
        print(expenses[0]['amount'])
        new_expense = expenses[1]
        new_expense['amount'] = 666
        conn.request('POST', '/money', json.dumps(new_expense),
                headers=headers)
        response = conn.getresponse()
        data = response.read()
        print("Status {}: {}".format(response.status, data))
        conn.request('GET', '/money', headers=headers)
        response = conn.getresponse()
        data = response.read()
        print("Status {}: {}".format(response.status, data))
        expenses = json.loads(str(data, 'utf-8'))
        print("Expenses number= {}".format(len(expenses)))
        conn.request('HEAD', '/money', headers=headers)
        response = conn.getresponse()
        data = response.read()
        print("Status {}: {}".format(response.status, data))
        conn.close()

