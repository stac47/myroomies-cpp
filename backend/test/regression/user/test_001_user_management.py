#!/usr/bin/env python3
# vi:set fileencoding=utf-8 :

"""
Created on 2016-01-14

@author : Laurent Stacul
"""

import logging
import unittest
import http.client
import json
import base64

from myroomies.server import MyRoomiesServer
from myroomies.server import create_houseshare
from myroomies.tools import add_authorization_header
from myroomies.models import User

class UserManagementOperations(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls._server = MyRoomiesServer()
        cls._server.start()
        cls.conn = http.client.HTTPConnection('localhost', 8080)

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()
        cls._server.stop()

    def test_user_creation(self):
        houseshare_id, roomies = create_houseshare(3)

        # Log in as a user of houseshare id 1 and retrieve all the roomies
        # from this user's houseshare
        headers = {}
        add_authorization_header(headers,
                                 roomies[0].login,
                                 roomies[0].password)
        self.conn.request('GET', '/user', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        logging.debug(str(data, 'utf-8'))
        self.assertEqual(200, response.status)
        users_list = \
            json.loads(str(data, 'utf-8'), object_hook=User.from_json)
        self.assertEqual(3, len(users_list))
        for user in users_list:
            self.assertEqual(houseshare_id, user.houseshare_id)

