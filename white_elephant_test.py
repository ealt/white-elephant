import numpy as np
import unittest

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate(self):
        actual = white_elephant.simulate(4)
        expected = np.array([
            [1, 1, 0, 0],
            [1, 1, 0, 0],
            [0, 0, 2, 0],
            [0, 0, 0, 2],
        ], np.uint64)
        self.assertTrue(np.array_equal(actual, expected))

    def test_simulate_bad_arg(self):
        with self.assertRaises(TypeError):
            white_elephant.simulate()


if __name__ == '__main__':
    unittest.main()
