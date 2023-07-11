#!/usr/bin/python3

"""Defineing a fiunction"""
def add_integer(a, b=98):
    """"  """
    if not isinstance(b, int) and not isinstance(b, float):
        raise TypeError("b must be an integer")
    if not isinstance(a, int) and not isinstance(a, float):
        raise TypeError("a must be an integer")
    else:
        sum = int(a) + int(b)
        return sum

