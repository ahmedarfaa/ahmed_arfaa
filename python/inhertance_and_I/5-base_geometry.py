#!/usr/bin/python3

class BaseGeometry:
    pass

    def area(self):
        raise Exception ("area() is not implemented")
    def integer_validator(self, name, value):
        
        if type(value) != int:
            raise TypeError("{} must be an integer". format(value))
        if value <= 0:
            raise ValueError("{} must be greater than 0". format(value))