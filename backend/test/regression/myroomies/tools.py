import logging
import base64


ADMIN_CREDENTIAL = ("admin", "PASSWORDHASH")

def add_authorization_header(headers, user, password):
    clear_basic = "{}:{}".format(user, password)
    base64_basic = base64.b64encode(clear_basic.encode('ASCII')).decode('ASCII')
    logging.debug("Authorisation: {} -> {}".format(clear_basic, base64_basic))
    headers["Authorization"] = "Basic {}".format(base64_basic)

def add_admin_authorization_header(headers):
    add_authorization_header(headers, *ADMIN_CREDENTIAL)
