#!/usr/bin/python3
def divisible_by_2(my_list=[]):
    orignl = my_list[:]
    for cout,i in enumerate(my_list):
        if i % 2 == 0:
            orignl[i] = True
        else:
            orignl[i] = False
    return orignl