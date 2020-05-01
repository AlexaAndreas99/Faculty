'''
Created on 5 Feb 2019

@author: Andreas-PC
'''
from texttable import Texttable
from program.exception import GameException 
class Board():
    def __init__(self):
        self._data=[]
        for i in range(0,6):
            self._data.append([' ']*6)
    
    def __str__(self):
        t=Texttable()
        for i in range(0,6):
            t.add_row(self._data[i])
        return t.draw()
    def is_won(self):
        copy=[]
    
        for i in range(0,16):
            copy.append([' ']*16)
            
        for i in range(5,11):
            for j in range(5,11):
                copy[i][j]=self._data[i-5][j-5]
        
        
        for i in range(5,11):
            for j in range(5,11):
                if copy[i][j]=='x' or copy[i][j]=='o':
                    
                    if copy[i][j]==copy[i+1][j+1]==copy[i+2][j+2]==copy[i+3][j+3]==copy[i+4][j+4]:
                        return True
                    elif copy[i][j]==copy[i+1][j]==copy[i+2][j]==copy[i+3][j]==copy[i+4][j]:
                        return True
                    elif copy[i][j]==copy[i+1][j-1]==copy[i+2][j-2]==copy[i+3][j-3]==copy[i+4][j-4]:
                        return True
                    elif copy[i][j]==copy[i][j-1]==copy[i][j-2]==copy[i][j-3]==copy[i][j-4]==copy[i][j-5]:
                        return True
                    elif copy[i][j]==copy[i-1][j-1]==copy[i-2][j-2]==copy[i-3][j-3]==copy[i-4][j-4]:
                        return True
                    elif copy[i][j]==copy[i-1][j]==copy[i-2][j]==copy[i-3][j]==copy[i-4][j]==copy[i-5][j]:
                        return True
                    elif copy[i][j]==copy[i+1][j-1]==copy[i+2][j-2]==copy[i+3][j-3]==copy[i+4][j-4]:
                        return True
                    elif copy[i][j]==copy[i][j+1]==copy[i][j+2]==copy[i][j+3]==copy[i][j+4]:
                        return True
        return False
    
    def free_space(self):
        l=[]
        for i in range(0,6):
            for j in range(0,6):
                xy=[]
                if self._data[i][j]==' ':
                    xy.append(i)
                    xy.append(j)
                    l.append(xy)
        return l
    def is_tie(self):
        if len(self.free_space())==0:
            return True
        return False
        
    def move(self,x,y,symbol):
        if x not in[0,1,2,3,4,5]:
            raise GameException("Invalid move!")
        
        if y not in[0,1,2,3,4,5]:
            raise GameException("Invalid move!")
        if symbol not in['x','o']:
            raise GameException("Invalid move!")
        if self._data[x][y]!=' ':
            raise GameException("Invalid move!")
        self._data[x][y]=symbol
        
    
#b=Board()
#b.move(5, 5, 'x')
#b.move(5, 1, 'x')
#b.move(5, 2, 'x')
#b.move(5, 3, 'x')
#b.move(5, 4, 'x')
#print(b.free_space())