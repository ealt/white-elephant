import numpy as np
import unittest

import heap


class HeapTest(unittest.TestCase):

    def test_get_mins(self):
        input = np.array([5, 3, 1, 4, 2, 0], dtype=np.uint32)
        actual = heap.get_mins(input)
        expected = np.array([5, 3, 1, 1, 1, 0], dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))

    def test_heap_sort(self):
        input = np.array([5, 3, 1, 4, 2, 0], dtype=np.uint32)
        actual = heap.heap_sort(input)
        expected = np.array([0, 1, 2, 3, 4, 5], dtype=np.uint32)
        self.assertTrue(np.array_equal(actual, expected))


if __name__ == '__main__':
    unittest.main()
