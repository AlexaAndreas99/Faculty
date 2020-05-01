'''
Created on 5 Feb 2019

@author: Andreas-PC
'''
from program.board import Board
from random import choice
class Game():
    def __init__(self):
        self._board=Board()
        
    def movehuman(self,x,y,symbol):
        self._board.move(x, y, symbol)
        
    def movecomputer(self):
        '''
        the computer blocks the human player's 1-move wins, if possible
        or makes a random valid move
        input: nothing
        output: puts x/o on the table
        '''
        
        
        for i in range(0,6):
            for j in range(0,6):
                if self._board._data[i][j]==' ':
                    self._board._data[i][j]='x'
                    if self._board.is_won():
                        self._board._data[i][j]='o'
                        return
                    else:
                        self._board._data[i][j]=' '
        
        for i in range(0,6):
            for j in range(0,6):
                if self._board._data[i][j]==' ':
                    self._board._data[i][j]='o'
                    if self._board.is_won():
                        self._board._data[i][j]='x'
                        return
                    else:
                        self._board._data[i][j]=' '
        
        
        l=self._board.free_space()
        c=choice(l)
        symbol=choice(['x','o'])
        self._board.move(c[0], c[1],symbol )
        
    def save_game(self):
        f=open("order&chaos.txt",'w')
        
        for i in range(0,6):
            for j in range(0,6):
                
                if self._board._data[i][j]==' ':
                    f.write('+')
                else:
                    f.write(self._board._data[i][j])
            f.write('\n')
        f.close()
        
    def load_game(self):
        f=open("order&chaos.txt",'r')
        line=f.readline()
        i=0
        while len(line)>2:
            tok=line.split()
            if tok[0][0]=='+':
                self._board._data[i][0]=' '
            else:
                self._board._data[i][0]=tok[0][0]
            if tok[0][1]=='+':
                self._board._data[i][1]=' '
            else:
                self._board._data[i][1]=tok[0][1]
            if tok[0][2]=='+':
                self._board._data[i][2]=' '
            else:
                self._board._data[i][2]=tok[0][2]
            
            if tok[0][3]=='+':
                self._board._data[i][3]=' '
            else:
                self._board._data[i][3]=tok[0][3]
            
            if tok[0][4]=='+':
                self._board._data[i][4]=' '
            else:
                self._board._data[i][4]=tok[0][4]
            
            if tok[0][5].strip()=='+':
                self._board._data[i][5]=' '
            else:
                self._board._data[i][5]=tok[0][5].strip()
            line=f.readline()
            i+=1
        f.close()
        
        
        
def test_computer():
    g=Game()
    
    g._board.move(1, 1, 'x')
    g._board.move(2, 2, 'x')
    g._board.move(3, 3, 'x')
    g._board.move(4, 4, 'x')
    g.movecomputer()
    assert g._board._data[0][0]=='o'
    
    n=len(g._board.free_space())
    g.movecomputer()
    m=len(g._board.free_space())
    assert n!=m

test_computer()