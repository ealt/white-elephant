import numpy as np
import unittest
from math import factorial

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate(self):
        n = 4
        actual = white_elephant.simulate(n)
        print(actual)
        expected = factorial(n - 1) * np.ones((n, n), np.uint64)
        self.assertTrue(np.array_equal(actual, expected))

    def test_simulate_bad_arg(self):
        with self.assertRaises(TypeError):
            white_elephant.simulate()


if __name__ == '__main__':
    unittest.main()
