#!/usr/bin/env python3
# vi:set fileencoding=utf-8 :

"""
Created on 2016-01-14

@author : Laurent Stacul
"""

import logging
import http.client
import json


class MyRoomiesClient(object):
    
    def __init__(self, host='localhost', port=8080):
        self.conn = http.client.HTTPConnection(host, port)

    def close(self):
        self.conn.close()

    def request(self, method, url, body="", headers={}, dump=True):
        if dump:
            dump_str = "Request  [{} {}]".format(method, url)
            if len(body) > 0:
                dump_str += ":\n" + self.__json_pretty_print(body)
            logging.debug(dump_str)

        self.conn.request(method, url, body, headers)
        response = self.conn.getresponse()
        data = str(response.read(), 'utf-8')
        if dump:
            dump_str = "Response [{}]".format(response.status)
            if len(data) > 0:
                dump_str += ":\n" + self.__json_pretty_print(data)
            logging.debug(dump_str)
        return (response.status, data)

    def __json_pretty_print(self, s=""):
        return json.dumps(json.loads(s), indent=4)

