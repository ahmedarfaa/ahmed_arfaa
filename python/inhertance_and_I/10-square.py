#!/usr/bin/python3

Rectangle = __import__('9-rectangle').Rectangle


class Square(Rectangle):
    """Represent ASquare."""

    def __init__(self, size):
        """Initialize a new square.
        """
        self.integer_validator("size", size)
        self.__size = size
        super().__init__(self.__size, self.__size)
