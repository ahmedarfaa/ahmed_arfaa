#!/usr/bin/python3
"""Define a Square class"""
class Square:
    """ initalization of the class """
    def __init__(self, size = 0):
        """
        args:
        size (int) : the size of new square
        """
        if not isinstance(size, int):
            raise TypeError("type must be integer")
        elif size < 0:
            raise ValueError("size should be >= ")
        self.__size = size