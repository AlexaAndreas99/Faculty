from connect4.exception import *
from connect4.game import *
from random import choice
class UI:
    def __init__(self,game):
        self._game=game
    
    def readMove(self):
        
        while True:
            try:
                hmove=input("Enter move> ")
                return hmove
                
            except Exception:
                print("Invalid input!")
            
    def start(self):
        b=self._game.board
        turn=[True,False]
        
        playerturn=choice(turn)
        
        while b.is_won()==False and b.is_tie()==False:
            if playerturn:
                print(self._game.board)
                try:
                    hmove=self.readMove()
                    self._game.movehuman(hmove)
                    print(self._game.board)
                except GameException as e:
                    print(e.message)
                    continue
            else:
                self._game.movecomputer()
            playerturn= not playerturn
            
        print(23*'-'+"Game over!"+22*'-')
        print(b)
        
        if b.is_won():
            if playerturn==False:
                print(22*'-'+"Player won!"+21*'-')
            else:
                print(22*'-'+"Computer won!"+21*'-')
                
        else:
            print(22*'-'+"Tie"+21*'-')
            

        


g=Game()
ui=UI(g)
ui.start()