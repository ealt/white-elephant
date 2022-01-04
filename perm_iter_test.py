import numpy as np
import unittest

import perm_iter


class PermIterTest(unittest.TestCase):

    def test_init_perm(self):
        n = 4
        actual = perm_iter.get_rand_perms(n, 1)
        expected = np.array([[i for i in range(n)]], dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))

    def test_next(self):
        n = 4
        actual = perm_iter.get_perms(n)
        expected = np.array([
            [0, 1, 2, 3],
            [1, 0, 2, 3],
            [2, 0, 1, 3],
            [0, 2, 1, 3],
            [1, 2, 0, 3],
            [2, 1, 0, 3],
            [3, 1, 0, 2],
            [1, 3, 0, 2],
            [0, 3, 1, 2],
            [3, 0, 1, 2],
            [1, 0, 3, 2],
            [0, 1, 3, 2],
            [0, 2, 3, 1],
            [2, 0, 3, 1],
            [3, 0, 2, 1],
            [0, 3, 2, 1],
            [2, 3, 0, 1],
            [3, 2, 0, 1],
            [3, 2, 1, 0],
            [2, 3, 1, 0],
            [1, 3, 2, 0],
            [3, 1, 2, 0],
            [2, 1, 3, 0],
            [1, 2, 3, 0],
        ],
                            dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))

    def test_rand_next(self):
        n = 4
        k = 10
        actual = perm_iter.get_rand_perms(n, k)
        excepted = set(range(n))
        for row in actual:
            self.assertSetEqual(set(row), excepted)


if __name__ == '__main__':
    unittest.main()
