#!/usr/bin/python3

BaseGeometry = __import__('5-base_geometry').BaseGeometry
class Rectangle(BaseGeometry):

    def __init__(self, width, height):
        """Intialize A-new_Rectangle.
        """
        self.integer_validator("width", width)
        self.__width = width
        self.integer_validator("height", height)
        self.__height = height