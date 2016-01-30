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

from myroomies.server import MyRoomiesServer

class MoneyBasicOperations(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls._server = MyRoomiesServer()
        cls._server.start()
        cls.conn = http.client.HTTPConnection('localhost', 8080)

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()
        cls._server.stop()

    def setUp(self):
        self.headers = {}
        self.headers['Authorization'] =  'Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=='

    def test_retrieve_no_authorization(self):
        self.conn.request('GET', '/money')
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(401, response.status)
        self.assertEqual(0, len(data))

    def test_retrieve_success(self):
        self.conn.request('GET', '/money', headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertTrue(len(data) > 0)
        expenses = json.loads(str(data, 'utf-8'))
        self.assertEqual(0, len(expenses))

    def test_access_unauthorized_method(self):
        self.conn.request('HEAD', '/money', headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(405, response.status)
        self.assertEqual(0, len(data))

        # self.assertrEqual(12.5, expenses[0]['amount'])
        # new_expense = expenses[1]
        # new_expense['amount'] += 6.0
        # new_expense['comment'] = "new comment"
        # new_expense['id'] = 14
        # new_expense_str =  json.dumps(new_expense)
        # print(new_expense_str)
        # conn.request('POST', '/money', new_expense_str,
        #         headers=headers)
        # response = conn.getresponse()
        # data = response.read()
        # print("Status {}: {}".format(response.status, data))
        # conn.request('GET', '/money', headers=headers)
        # response = conn.getresponse()
        # data = response.read()
        # print("Status {}: {}".format(response.status, data))
        # expenses = json.loads(str(data, 'utf-8'))
        # print("Expenses number= {}".format(len(expenses)))

