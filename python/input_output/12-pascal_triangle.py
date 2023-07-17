#!/usr/bin/python3
import json

def pascal_triangle(n):

    
    if n <= 0 :
        return []
    traingle = []
    raw = [1]
    traingle.append(raw)

    for i in range (1,n):
        new_raw =[1]
        for j in range (1, i):
            new_raw.append(traingle[i-1][j-1] + traingle[i-1][j])
        new_raw.append(1)
        traingle.append(new_raw)

    return traingle        



