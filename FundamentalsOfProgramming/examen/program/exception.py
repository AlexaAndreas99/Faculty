'''
Created on 5 Feb 2019

@author: Andreas-PC
'''
class GameException(Exception):
    def __init__(self,msg):
        self._msg=msg
        
    @property
    def message(self):
        return self._msg