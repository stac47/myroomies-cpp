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
from myroomies.client import MyRoomiesClient
from myroomies.tools import add_authorization_header
from myroomies.models import User

class UserManagementOperations(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls._server = MyRoomiesServer()
        cls._server.start()
        cls.client = MyRoomiesClient('localhost', 8080)
        cls.houseshare_id, cls.roomies = create_houseshare(3)


    @classmethod
    def tearDownClass(cls):
        cls.client.close()
        cls._server.stop()

    def test_user_creation(self):
        # Log in as a user of houseshare id 1 and retrieve all the roomies
        # from this user's houseshare
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        status, data = self.client.request('GET', '/users', headers=headers)
        self.assertEqual(200, status)
        users_list = \
            json.loads(data, object_hook=User.from_json)
        self.assertEqual(3, len(users_list))
        for user in users_list:
            self.assertEqual(self.houseshare_id, user.houseshare_id)

    def test_get_user(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        status, data =\
            self.client.request('GET', '/users/me', headers=headers)
        self.assertEqual(200, status)
        logged_user = \
            json.loads(data , object_hook=User.from_json)
        self.assertEqual(self.roomies[0].user_id, logged_user.user_id)

