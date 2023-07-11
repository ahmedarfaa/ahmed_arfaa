#!/usr/bin/python3
def delete_at(my_list=[], idx=0):
    if idx < 0 or idx > len(my_list):
        return my_list
    else:
        new = my_list
        for i in range(len(new)):
            if i == idx:
                pass
            else:
                return new
