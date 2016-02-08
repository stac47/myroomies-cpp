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
from myroomies.server import create_houseshare
from myroomies.tools import add_authorization_header
from myroomies.tools import add_admin_authorization_header


class CreateExpense(object):
    counter = 0

    def __call__(self):
        self.counter += 1
        new_expense = {}
        new_expense['date'] = "2016-01-15"
        new_expense['amount'] = 6.0 + self.counter
        new_expense['title'] = "title_{}".format(self.counter)
        new_expense['comment'] = "comment_{}".format(self.counter)
        return new_expense

create_expense = CreateExpense()

class MoneyBasicOperations(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls._server = MyRoomiesServer()
        cls._server.start()
        cls.conn = http.client.HTTPConnection('localhost', 8080)
        cls.houseshare_id, cls.roomies = create_houseshare(3)

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()
        cls._server.stop()

    def tearDown(self):
        headers = {}
        add_admin_authorization_header(headers)
        self.conn.request('GET', '/money', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        retrieved_expenses = json.loads(str(data, 'utf-8'))
        for expense in retrieved_expenses:
            self.conn.request('DELETE',
                              '/money/{}'.format(expense["id"]),
                              headers=headers)
            response = self.conn.getresponse()
            response.read()
            self.assertEqual(200, response.status)

    def test_retrieve_no_authorization(self):
        self.conn.request('GET', '/money')
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(401, response.status)
        self.assertEqual(0, len(data))

    def test_retrieve_nothing(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        self.conn.request('GET', '/money', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertEqual('[]', str(data, 'utf-8'))

    def test_access_unauthorized_method(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        self.conn.request('HEAD', '/money', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(405, response.status)
        self.assertEqual(0, len(data))

    def test_create_delete(self):
        new_expense = create_expense()
        new_expense_str =  json.dumps(new_expense)
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)

        # Inserting a new expense
        self.conn.request('POST', '/money', new_expense_str, headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        logging.debug(str(data, 'utf-8'))
        self.assertEqual(200, response.status)
        self.assertTrue(len(data) > 0)
        inserted_expense = json.loads(str(data, 'utf-8'))
        self.assertEqual(new_expense['date'], inserted_expense['date'])

        # Retrieve a list of expenses
        self.conn.request('GET', '/money', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertTrue(len(data) > 0)
        retrieved_expense = json.loads(str(data, 'utf-8'))
        self.assertEqual(1, len(retrieved_expense))

        # Delete the expense
        self.conn.request('DELETE',
                          '/money/{}'.format(retrieved_expense[0]["id"]),
                          headers=headers)
        response = self.conn.getresponse()
        self.assertEqual(200, response.status)
        data = response.read()
        self.assertEqual(0, len(data))

        # Check there is no expense at the end of this test
        self.conn.request('GET', '/money', headers=headers)
        response = self.conn.getresponse()
        data = response.read()
        self.assertEqual(200, response.status)
        self.assertEqual("[]", data.decode('utf-8'))

    def test_unauthorized_delete(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)

        # Nothing to delete => 404
        self.conn.request('DELETE',
                          '/money/{}'.format(12),
                          headers=headers)
        response = self.conn.getresponse()
        response.read()
        self.assertEqual(404, response.status)

        # Rotten request
        self.conn.request('DELETE',
                          '/money/{}'.format("wrong"),
                          headers=headers)
        response = self.conn.getresponse()
        response.read()
        self.assertEqual(400, response.status)

        new_expense = create_expense()
        new_expense_str =  json.dumps(new_expense)
        self.conn.request('POST', '/money', new_expense_str, headers=headers)
        response = self.conn.getresponse()
        self.assertEqual(200, response.status)
        data = response.read()
        retrieved_expense = json.loads(str(data, 'utf-8'))

        # An other roomie tries to erase an expense not belonging to himself
        add_authorization_header(headers,
                                 self.roomies[1].login,
                                 self.roomies[1].password)
        self.conn.request('DELETE',
                          '/money/{}'.format(retrieved_expense["id"]),
                          headers=headers)
        response = self.conn.getresponse()
        response.read()
        self.assertEqual(403, response.status)
