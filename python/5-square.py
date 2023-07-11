#!/usr/bin/python3

class Square:
    def __init__(self, size = 0):
        """
        """
        self.__size = size
    @property
    def size(self):
        return (self.__size)
    
    @size.setter
    def size(self, value):
        if not isinstance(value, int):
            raise TypeError("should be integer")
        elif value < 0:
            raise ValueError("shoulde be >= 0")
        self.__size = value
    def area(self):
        return (self.__size * self.__size)
    def my_print(self):
        
        for i in range(0,self.__size):
            for j in range(self.__size):
                print("#", end="")
            print("")
        if self.__size == 0:
            print("")