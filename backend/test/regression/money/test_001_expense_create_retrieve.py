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
from myroomies.client import MyRoomiesClient
from myroomies.tools import add_authorization_header
from myroomies.tools import add_admin_authorization_header


class CreateExpense(object):
    counter = 0

    def __call__(self):
        self.counter += 1
        new_expense = {}
        new_expense['date'] = "20160115"
        new_expense['amount'] = 6.0 + self.counter
        new_expense['title'] = "title_{}".format(self.counter)
        new_expense['comment'] = "comment_{}".format(self.counter)
        new_expense['tags'] = ["tag1", "tag2"]
        return new_expense

create_expense = CreateExpense()

class MoneyBasicOperations(unittest.TestCase):

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

    def tearDown(self):
        headers = {}
        add_admin_authorization_header(headers)
        status, data = self.client.request('GET', '/money', headers=headers)
        self.assertEqual(200, status)
        retrieved_expenses = json.loads(data)
        for expense in retrieved_expenses:
            status, _ = self.client.request('DELETE',
                                            '/money/{}'.format(expense["id"]),
                                            headers=headers)
            self.assertEqual(200, status)

    def test_retrieve_no_authorization(self):
        status, data = self.client.request('GET', '/money')
        self.assertEqual(401, status)
        self.assertEqual(0, len(data))

    def test_retrieve_nothing(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        status, data = self.client.request('GET', '/money', headers=headers)
        self.assertEqual(200, status)
        self.assertEqual('[]', data)

    def test_access_unauthorized_method(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)
        status, data = self.client.request('HEAD', '/money', headers=headers)
        self.assertEqual(405, status)
        self.assertEqual(0, len(data))

    def test_create_delete(self):
        new_expense = create_expense()
        new_expense_str =  json.dumps(new_expense)
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)

        # Inserting a new expense
        status, data =\
            self.client.request('POST', '/money', new_expense_str, headers=headers)
        self.assertEqual(200, status)
        self.assertTrue(len(data) > 0)
        inserted_expense = json.loads(data)
        self.assertEqual(new_expense['date'], inserted_expense['date'])

        # Retrieve a list of expenses
        status, data = self.client.request('GET', '/money', headers=headers)
        self.assertEqual(200, status)
        self.assertTrue(len(data) > 0)
        retrieved_expense = json.loads(data)
        self.assertEqual(1, len(retrieved_expense))

        # Delete the expense
        status, data =\
            self.client.request('DELETE',
                                '/money/{}'.format(retrieved_expense[0]["id"]),
                                headers=headers)
        self.assertEqual(200, status)
        self.assertEqual(0, len(data))

        # Check there is no expense at the end of this test
        status, data = self.client.request('GET', '/money', headers=headers)
        self.assertEqual(200, status)
        self.assertEqual("[]", data)

    def test_unauthorized_delete(self):
        headers = {}
        add_authorization_header(headers,
                                 self.roomies[0].login,
                                 self.roomies[0].password)

        # Nothing to delete => 404
        status, _ =\
            self.client.request('DELETE',
                                '/money/{}'.format(12),
                                headers=headers)
        self.assertEqual(404, status)

        # Rotten request
        status, _ =\
            self.client.request('DELETE',
                                '/money/{}'.format("wrong"),
                                headers=headers)
        self.assertEqual(400, status)

        new_expense = create_expense()
        new_expense_str =  json.dumps(new_expense)
        status, data =\
            self.client.request('POST', '/money', new_expense_str, headers=headers)
        self.assertEqual(200, status)
        retrieved_expense = json.loads(data)

        # An other roomie tries to erase an expense not belonging to himself
        add_authorization_header(headers,
                                 self.roomies[1].login,
                                 self.roomies[1].password)
        status, _ =\
            self.client.request('DELETE',
                                '/money/{}'.format(retrieved_expense["id"]),
                                headers=headers)
        self.assertEqual(403, status)
