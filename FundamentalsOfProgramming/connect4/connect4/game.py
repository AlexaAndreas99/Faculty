from connect4.table import Board
from random import choice, choices
class Game:
    def __init__(self):
        self._board=Board()
        
    @property
    def board(self):
        return self._board
    
    def movehuman(self,column):
        self._board.move(column, 'r')
    
    
    def movecomputer(self):
        options=self.board.free_columns()
        
        '''
        move to win
        '''
        for j in range(0,7):
            i=self.board.column_oc(j)
            if self.board._data[i-1][j]==' ':
                self.board._data[i-1][j]='g'
                if self.board.is_won():
                    self.board._data[i-1][j]='g'
                    return
                else:
                    self.board._data[i-1][j]=' '
        
        
        '''
        if player wins
        '''
                
        for j in range(0,7):
            i=self.board.column_oc(j)
            if self.board._data[i-1][j]==' ':
                self.board._data[i-1][j]='r'
                if self.board.is_won():
                    self.board._data[i-1][j]='g'
                    return
                else:
                    self.board._data[i-1][j]=' '
                    
        self.board.move(choice(options), 'g')
        