#My Roomies - Backend

This is the server part of the project. Its main responsibilities are:
* Serving HTTP request
* Marshalling / Unmarshalling JSON Responses / Requests
* Persisting the data in an sqlite3 database

Hereafters is the services references.

## Security

Generally, accessing services requires credential validation. Credentials have
to be passed in the __Authorization__ HTTP header. The basic method is used
here meaning the value of this header will be ''Basic <base64 of
login:password>''.

User management services are protected and only the 'admin' user is able to
add/remove users.

## Services Interfaces

### Users Management

#### Retrieve

##### GET <root-uri>/user

Retrieve the list of the users belonging to the logged user's houseshare. If the
logged user is 'admin', retrieve all the registered users.

Reply example:

    [{
        "id" : 12,
        "login": "user1",
        "password": "password1",
        "firstname": "firstname1",
        "lastname": "lastname1",
        "dateOfBirth": "1984-03-11",
        "email": "user1@host.com",
        "houseshareId": 1
    },
    {
        "id" : 13,
        "login": "user2",
        "password": "password2",
        "firstname": "firstname2",
        "lastname": "lastname2",
        "dateOfBirth": "1986-05-14",
        "email": "user2@host.com",
        "houseshareId": 1
    }]

##### GET <root-uri>/user/me

Retrieve the current logged user profile. This is generally the first message
sent by a GUI to myroomies server.

This service cannot fail except if bad credentials are provided in the basic
HTTP authorization header.

Reply example:

    {
        "id" : 12,
        "login": "user1",
        "password": "password1",
        "firstname": "firstname1",
        "lastname": "lastname",
        "dateOfBirth": "1984-03-11",
        "email": "user1@host.com",
        "houseshareId": 1
    }

##### GET <root-uri>/user/<user-id>

Retrieve <user-id>'s profile information.

If the logged user does not share the same houseshare and is not 'admin' user,
the HTTP error __403__ is returned.

If the <user-id> does not exist a __404__ error is returned.

Reply example:

    {
        "id" : 12,
        "login": "user1",
        "password": "password1",
        "firstname": "firstname1",
        "lastname": "lastname",
        "dateOfBirth": "1984-03-11",
        "email": "user1@host.com",
        "houseshareId": 1
    }

#### Create

##### POST <root-uri>/user

Create a user. Only 'admin' can perform this action otherwise an error __403__
is returned.

In case of success, HTTP error code __200__ is returned and the reply contains
the stored user profile.

Query example:

    {
        "login": "user1",
        "password": "password1",
        "firstname": "firstname1",
        "lastname": "lastname",
        "dateOfBirth": "1984-03-11",
        "email": "user1@host.com",
        "houseshareId": 1
    }

Reply example:

    {
        "id" : 12,
        "login": "user1",
        "password": "password1",
        "firstname": "firstname1",
        "lastname": "lastname",
        "dateOfBirth": "1984-03-11",
        "email": "user1@host.com",
        "houseshareId": 1
    }

#### Delete

##### DELETE <root-uri>/user

Delete a user. Only 'admin' can perform this action otherwise an error __403__
is returned.

In case of success, HTTP error code __200__ is returned and the user is
deleted.

### Money Management

#### Expense: Retrieve GET <root-uri>/money

Retrieve the list of expenses of the logged user's houseshare.

Reply example:

    [{
        "id": 1,
        "amount": 8.0,
        "userId": 2,
        "title": "title_2",
        "date": "20160115",
        "comment": "comment_2",
        "houseshareId": 1
    },
    {
        "id": 2,
        "amount": 14.0,
        "userId": 1,
        "title": "title_4",
        "date": "20160115",
        "comment": "comment_4",
        "houseshareId": 1
    }]

#### Expense: Create POST <root-uri>/money

Create an expense on behalf of the houseshare of the logged user.

A new expense request is valid if it contains the following mandatory elements:
amount, date, title. If one of this element is missing an error __400__ is
returned.

The reply contains consolidated data about the expense (id, houseshareId).

Query example:

	{
		"amount": 8.0,
		"comment": "comment_2",
		"title": "title_2",
		"date": "20160115",
        "tags": [
            "tag1",
            "tag2"
        ]
	}

Reply example:

	{
		"id": 1,
		"amount": 8.0,
		"userId": 2,
		"title": "title_2",
		"date": "20160115",
		"comment": "comment_2",
		"houseshareId": 1,
        "tags": [
            "tag1",
            "tag2"
        ]
	}

#### Expense: Delete DELETE <root-uri>/money/<id>

Delete the expense <id>.

If the expense <id> does not belong to the logged user, an error __403__ is
returned. If the expense <id> does not exist, an error __404__ is returned. If
<id> is not a numbe, an error __400__ is returned.

