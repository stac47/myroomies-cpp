import logging
logging.basicConfig(
    format='%(asctime)s [%(levelname)s] %(message)s',
    filename='regression.log',
    level=logging.DEBUG)

import unittest

if __name__ == "__main__":
    unittest.main()
