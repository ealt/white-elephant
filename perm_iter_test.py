import numpy as np
import unittest

import perm_iter


class PermIterTest(unittest.TestCase):

    def test_init_perm(self):
        n = 4
        actual = perm_iter.get_perms(n, 1)
        expected = np.array([[i for i in range(n)]], dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))

    def test_rand_next(self):
        n = 4
        k = 10
        actual = perm_iter.get_perms(n, k)
        excepted = set(range(n))
        for row in actual:
            self.assertSetEqual(set(row), excepted)


if __name__ == '__main__':
    unittest.main()
