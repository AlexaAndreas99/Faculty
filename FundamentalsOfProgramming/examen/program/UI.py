'''
Created on 5 Feb 2019

@author: Andreas-PC
'''
from program.exception import GameException
from program.game import Game
class UI():
    def __init__(self,game):
        self._game=game
        
    def read_move(self):
        while True:
            try:
                hmove=input("enter input> ")
                if hmove=='save':
                    self._game.save_game()
                    return hmove
            
                
                hmove=hmove.split()
                #if len(hmove<3):
                #    raise GameException("Invalid!")
                return hmove
            
            except Exception:
                print("Invalid input!")
        
        
    def start(self):
        player_turn=True
        inp=input("do you want to continue from where you saved? ")
        if inp=='yes':
            self._game.load_game()
        
        b=self._game._board
        while b.is_won()==False and b.is_tie()==False:
            
            if player_turn:
                print(b)
                try:
                    
                    hmove=self.read_move()
                    if hmove=='save':
                        return  
                    
                    hmove[1]=int(hmove[1])
                    hmove[0]=int(hmove[0])
                    self._game.movehuman(hmove[1],hmove[0],hmove[2])
                    #print(b)
                except GameException as e:
                    print(e.message)
                    continue
            else:
                self._game.movecomputer()
            player_turn= not player_turn
        if b.is_won()==True:
            print(b)
            
            print(23*'-',"Congratulations!",23*'-')
            print(23*'-',"You Won!",23*'-')
        elif b.is_tie()==True:
            print(b)
            print(23*'-',"You Lost!",23*'-')
    
g=Game()
ui=UI(g)
ui.start()       