import numpy as np
import unittest

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate(self):
        actual = white_elephant.simulate()
        expected = np.zeros((3, 4), np.uint64)
        self.assertTrue(np.array_equal(actual, expected))


if __name__ == '__main__':
    unittest.main()
