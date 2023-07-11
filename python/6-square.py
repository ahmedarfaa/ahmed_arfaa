#!/usr/bin/python3

class Square:
    def __init__(self, size = 0, position = (0, 0)):
        """
        """
        self.size = size
        self.position = position
    @property
    def size(self):
        return (self.__size)
    @property
    def position(self):
        return(self.__position)
    
    @size.setter
    def size(self, value):
        if not isinstance(value, int):
            raise TypeError("should be integer")
        elif value < 0:
            raise ValueError("shoulde be >= 0")
        self.__size = value
    @position.setter
    def position(self, value):
        if (not isinstance(value, tuple)
            or len(value)!= 2
            or not all(isinstance(num, int) for num in value) 
            or not all(num >= 0 for num in value)):
            raise TypeError("postion must be tuple")
        
        self._position = value

    def area(self):
        return (self.__size * self.__size)
    def my_print(self):
        
        for i in range(0,self.__size):
            for j in range(self.__size):
                print("#", end="")
            print("")
        if self.__size == 0:
            print("")