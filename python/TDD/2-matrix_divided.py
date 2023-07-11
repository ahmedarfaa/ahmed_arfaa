#!/usr/bin/python3
""" Def"""

def matrix_divided(matrix, div):
   if (not isinstance(matrix, list)) or matrix == [] or not all (isinstance(ele, int) or isinstance (ele, float) for ele in [num for raw in matrix for num in raw]):
      raise TypeError ("matrix must be a matrix (list of lists) of integers/floats")
      
   if not all((len(raw) == len(matrix[0]))for raw in matrix):
      raise TypeError("Each row of the matrix must have the same size")
   if not isinstance(div, int) and not isinstance(div, float):
      raise TypeError("div must be a number")
   if div == 0:
      raise ZeroDivisionError("division by zero")
   
   return ([list(map(lambda x : round(x / div, 2), raw ))for raw in matrix])