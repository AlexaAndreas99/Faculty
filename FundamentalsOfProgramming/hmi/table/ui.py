from game import game
from table import GameException
import random
class UI():
    def __init__(self,game):
        self._game=game
    
    def present(self):
        b=self._game._board
        print("In year",b._year,", ",b._starved,"people starved.")
        print(b._came," people came to the city.")
        print("City population is ",b._people)
        print("City owns ",b._acres," acres of land.")
        print("Harvest was ",b._harvest)
        print("Rats ate ",b._rats)
        print("Land price is ",b._landprice)
        print("Grain is ",b._grain)
        
    
    def start(self):
        b=self._game._board
        while b._year<5:
            self.present()
            print()
        
            a=int(input("Acres to buy/sell(+/-): "))
            p=int(input("units to feed the people: "))
            plant=int(input("units to plant: "))
            try:
                
                b.change(a,p,plant)
                b._year+=1
                b._landprice=random.randint(15,25)
                b._harvest=random.randint(1,6)
                
            except GameException as e:
                print(e.message)
                continue
        
g=game()
ui=UI(g)
ui.start()
        