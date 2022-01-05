import numpy as np
import unittest
from math import factorial

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate_all_games(self):
        n = 4
        actual = white_elephant.simulate(n)
        expected = factorial(n - 1) * np.ones((n, n), np.uint64)
        self.assertTrue(np.array_equal(actual, expected))

    def test_simulate_random_games(self):
        n = 4
        k = 10
        actual = white_elephant.simulate(n, k=k)
        expected = k * np.ones((n,), np.uint64)
        self.assertTrue(np.array_equal(np.sum(actual, axis=0), expected))
        self.assertTrue(np.array_equal(np.sum(actual, axis=1), expected))

    def test_simulate_bad_arg(self):
        with self.assertRaises(TypeError):
            white_elephant.simulate()


if __name__ == '__main__':
    unittest.main()
