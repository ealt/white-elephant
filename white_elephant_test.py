import numpy as np
import unittest

import white_elephant


class WhiteElephantTest(unittest.TestCase):

    def test_simulate(self):
        expected = np.zeros((3, 4), np.int32)
        self.assertTrue(np.array_equal(white_elephant.simulate(), expected))


if __name__ == '__main__':
    unittest.main()
