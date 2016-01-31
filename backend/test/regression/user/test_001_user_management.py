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

import myroomies.logging
from myroomies.server import MyRoomiesServer

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
        new_user = {}
        new_user['login'] = "user1"
        new_user['password'] = "password1"
        new_user['firstname'] = "firstname1"
        new_user['lastname'] = "lastname1"
        new_user['email'] = "email1@host.com"
        new_user['dateOfBirth'] = "1981-06-19"
        new_user['houseshareId'] = 1
        new_user_str = json.dumps(new_user)
        logging.debug(new_user_str)

        headers = {}
        headers['Authorization'] = 'Basic ' + \
            str(base64.b64encode("admin:PASSWORDHASH".encode()))
        self.conn.request('POST', '/user', new_user_str,
                          headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        logging.debug(str(data, 'utf-8'))
        self.assertEqual(200, response.status)
        inserted_user = json.loads(str(data, 'utf-8'))
        self.assertEqual(1, inserted_user['id'])

        # Retrieve all the roomies from houseshare 1
        headers['Authorization'] = 'Basic ' + \
            base64.b64encode("user1:password1")
        self.conn.request('GET', '/user', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        logging.debug(str(data, 'utf-8'))
        self.assertEqual(200, response.status)
        users_list = json.loads(str(data, 'utf-8'))
        self.assertEqual(1, len(users_list))

