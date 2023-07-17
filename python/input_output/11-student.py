#!/usr/bin/python3
import json

class Student:

    def __init__(self, first_name, last_name, age):
        self.first_name =first_name
        self.last_name= last_name
        self.age= age

    def to_json(self, attrs=None):
        
        if (type(attrs) == list and all(type(ele)== str for ele in attrs)):

            return {value: getattr(self, value) for value in attrs if hasattr(self, value)}

        return self.__dict__

    def reload_from_json(self, json):

        for key, value in json.items():
            setattr(self, key, value)
        