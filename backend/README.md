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

##### GET <root-uri>/users

Retrieve the list of the users belonging to the logged user houseshare. If the
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

##### GET <root-uri>/users/<user-id>

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

##### POST <root-uri>/users

Create a user.

If the logged user is 'admin', the new user must be provided with a valid
houseshare id otherwise an error __400__ is returned. If the logged user is not
'admin', an HTTP error __403__ is returned.

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

##### DELETE <root-uri>/users

Delete a user.

If the logged user is 'admin', the new user must be provided with a valid
houseshare id otherwise an error __400__ is returned. If the logged user is not
'admin', an HTTP error __403__ is returned.

In case of success, HTTP error code __200__ is returned and the user is
deleted.

### Money Management

#### Expense: Retrieve GET <root-uri>/money

Retrieve the list of expenses of the current logged user's houseshare.
