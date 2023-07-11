import unittest

max_integer = __import__('6-max_integer').max_integer

class TestMaxInteger(unittest.TestCase):

    def test_matrix_normal(self):
        res = max_integer([1 ,2 ,6 ,3])
        self.assertEqual(res, 6)

if __name__ == '__main__':
    unittest.main()

    