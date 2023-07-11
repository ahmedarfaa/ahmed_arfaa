import unittest

max_integer = __import__('6-max_integer').max_integer

class Test_max_integer(unittest.TestCase):

  def max_integer(self):
      result = max_integer([1, 2, 3, 4])
      self.assertEqual(result, 4)

  

if __name__ == '__main__':
    unittest.main()