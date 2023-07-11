#!/usr/bin/python3

"""dd"""
class Square:
    """ 'll"""
    def __init__(self, size = 0):
        """
        args :
        """
        self.__size = size

    @property
    def size(self):
            """ ggg"""
            return (self.__size)
        
    @size.setter
    def size(self, value):
            if not isinstance(value, int):
                raise TypeError("value should be integer")
            elif value < 0:
                raise ValueError("value shoud be >= 0")
            self.__size = value
    def area(self):
            """ lfkk"""
            return (self.__size * self.__size)