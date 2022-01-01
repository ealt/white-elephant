import numpy as np
import unittest

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate(self):
        actual = white_elephant.simulate(4)
        expected = np.zeros((4, 4), np.uint64)
        self.assertTrue(np.array_equal(actual, expected))

    def test_simulate_bad_arg(self):
        with self.assertRaises(TypeError):
            white_elephant.simulate()


if __name__ == '__main__':
    unittest.main()
