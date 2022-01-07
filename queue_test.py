import numpy as np
import unittest

import my_queue


class QueueTest(unittest.TestCase):

    def test_push_pop(self):
        input = np.array([2, 3, 1, 0, 1, 2, 3], dtype=np.uint32)
        actual = my_queue.push_pop(4, input, 3)
        expected = np.array([2, 3, 1, 0, 1, 2], dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))


if __name__ == '__main__':
    unittest.main()
