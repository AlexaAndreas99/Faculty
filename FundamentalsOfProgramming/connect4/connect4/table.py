from texttable import Texttable
from connect4.exception import GameException
import unittest

class Board:
    def __init__(self):
        self._data=[]
        for i in range(0,6):
            self._data.append([' ']*7)
        '''
        for i in range(0,12):
            for j in range(0,13):
                print(self._data[i][j])
            print()
        
        #print(self._data)
        '''    
    
    def move(self,column,symbol):
        if column not in ['0','1','2','3','4','5','6']:
            raise GameException("Move outside board!")
    
        column=int(column)
        if self.column_oc(column)==0:
            raise GameException("Column is full!")
        
        i=self.column_oc(column)
        self._data[i-1][column]=symbol
    
    '''
    returns how many free spaces are on a given column
    '''
    def column_oc(self,j):
        s=0
        j=int(j)
        for i in range(0,6):
            if self._data[i][j]==' ':
                s+=1
        return s
    
    '''
    returns the columns where you can still put at least one element
    '''
    def free_columns(self):
        res=[]
        for i in range(0,7):
            if self.column_oc(i)!=0:
                res.append(chr(ord(str(i))))
        return res
    
    def is_won(self):
        c=[]
        for i in range (0,12):
            c.append([' ']*13)
        for i in range(0,6):
            for j in range(0,7):
                c[i+3][j+3]=self._data[i][j]
        for i in range(3,9):
            for j in range(3,10):
                if c[i][j]!=' ':
                    if c[i][j]==c[i-1][j]==c[i-2][j]==c[i-3][j]:
                        return True
                    if c[i][j]==c[i-1][j+1]==c[i-2][j+2]==c[i-3][j+3]:
                        return True
                    if c[i][j]==c[i][j+1]==c[i][j+2]==c[i][j+3]:
                        return True
                    if c[i][j]==c[i+1][j+1]==c[i+2][j+2]==c[i+3][j+3]:
                        return True
                    if c[i][j]==c[i+1][j]==c[i+2][j]==c[i+3][j]:
                        return True
                    if c[i][j]==c[i+1][j-1]==c[i+2][j-2]==c[i+3][j-3]:
                        return True
                    if c[i][j]==c[i][j-1]==c[i][j-2]==c[i][j-3]:
                        return True
                    if c[i][j]==c[i-1][j-1]==c[i-2][j-2]==c[i-3][j-3]:
                        return True
        return False
                    
            
                
    
    def is_tie(self):
        return self.is_won()==False and len(self.free_columns())==0
    
    def __len__(self):
        return len(self._data)
    
    def __str__(self):
        t=Texttable()
        
        res=['0']
        i=6
        while i>0:
            res.append(chr(ord(res[-1])+1))
            i-=1
        
        t.header(res)
        
        for i in range(0,6):
            res=[]
            for j in range(0,7):
                res.append(self._data[i][j])
            t.add_row(res)
            #print(res)
            
        return t.draw()
    
class BoardTest(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
    
    def btest(self):
        b=Board()
        b.move('0', 'r')
        assert b.column_oc(0)==5
        b.move('0', 'r')
        b.move('0', 'r')
        b.move('0', 'r')
        assert b.is_won()==True
        b.move('0', 'r')
        b.move('0', 'r')
        assert len(b.free_columns())==6
s=BoardTest()
s.btest()