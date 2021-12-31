import unittest

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_hello_world(self):
        white_elephant.hello_world()


if __name__ == '__main__':
    unittest.main()
