#!/usr/bin/python3

BaseGeometry = __import__('5-base_geometry').BaseGeometry

class Rectangle(BaseGeometry):

    def __init__(self, width, height):
        self.integer_validator("width", width)
        self.__width = width
        self.integer_validator("height", height)
        self.__height = height
    def area(self):
        return (self.__height * self.__width)
    def __str__(self):
        return ("[{}] {}/{}". format(str(self.__class__.__name__),str(self.__width), self.__height))