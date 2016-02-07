import json

class User(object):
    user_id = 0
    houseshare_id = 0
    login = ""
    password = ""
    firstname = ""
    lastname = ""
    email = ""
    date_of_birth = ""

    @staticmethod
    def from_json(dct):
        u = User()
        u.user_id = dct['id']
        u.houseshare_id = dct['houseshareId']
        u.login = dct['login']
        u.firstname = dct['firstname']
        u.lastname = dct['lastname']
        u.email = dct['email']
        u.date_of_birth = dct['dateOfBirth']
        return u

class UserEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, User):
            return { 'id': obj.user_id,
                     'houseshareId': obj.houseshare_id,
                     'login': obj.login,
                     'password': obj.password,
                     'firstname': obj.firstname,
                     'lastname': obj.lastname,
                     'email': obj.email,
                     'dateOfBirth': obj.date_of_birth}

if __name__ == '__main__':
    u = User()
    u.login = "user"
    u.houseshare_id = 1
    u.password = "password"
    u.firstname = "firstname"
    u.lastname = "lastname"
    u.email = "email@host.com"
    u.date_of_birth = "1981-06-19"
    s = json.dumps(u, cls=UserEncoder)
    print(s)
    u = json.loads(s, object_hook=User.from_json)
    print(json.dumps(u, cls=UserEncoder))

