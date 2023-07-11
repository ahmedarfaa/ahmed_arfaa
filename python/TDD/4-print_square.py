#!/usr/bin/python3

def print_square(size):
    if not isinstance(size, int) or isinstance (size, float) or size < 0:
        raise TypeError("size must be an integer")
    if size < 0:
        raise ValueError ("size must be >= 0")
    
    for i in range (size):
        [print("#", end="") for j in range (size)]
        print()
    