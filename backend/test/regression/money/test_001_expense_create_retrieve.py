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

    def test_retrieve_nothing(self):
        self.conn.request('GET', '/money', headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertEqual('[]', str(data, 'utf-8'))
        expenses = json.loads(str(data, 'utf-8'))
        self.assertEqual(0, len(expenses))

    def test_access_unauthorized_method(self):
        self.conn.request('HEAD', '/money', headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(405, response.status)
        self.assertEqual(0, len(data))

    def test_create_delete(self):
        new_expense = {}
        new_expense['date'] = "2016-01-15"
        new_expense['amount'] = 6.0
        new_expense['title'] = "bakerie"
        new_expense['comment'] = "new comment"
        new_expense_str =  json.dumps(new_expense)
        logging.debug(new_expense_str)

        # Inserting a new expense
        self.conn.request('POST', '/money', new_expense_str,
                          headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        logging.debug(str(data, 'utf-8'))
        self.assertEqual(200, response.status)
        self.assertTrue(len(data) > 0)
        inserted_expense = json.loads(str(data, 'utf-8'))
        self.assertEqual(new_expense['date'], inserted_expense['date'])

        # Retrieve a list of expenses
        self.conn.request('GET', '/money', headers=self.headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertTrue(len(data) > 0)
        retrieved_expense = json.loads(str(data, 'utf-8'))
        self.assertEqual(1, len(retrieved_expense))

