class Board():
    def __init__(self):
        self._year=1
        self._starved=0
        self._people=100
        self._came=0
        self._acres=1000
        self._harvest=3
        self._rats=200
        self._grain=2800
        self._landprice=20
   
    def is_lost(self):
        pass
    
    def change(self,a,p,plant):
        if self._grain-(self._landprice*a)<0:
            raise GameException("Not enough minerals!")
        if self._acres+a<0:
            raise GameException("Not enough acres!")
        self._acres+=a
        print(self._grain)
        if a<0:
            self._grain-=self._landprice*a
        else:
            self._grain-=self._landprice*a
        print(self._grain)
        if self._grain-p<0:
            raise GameException("Not enough minerals to feed the people!")
        self._grain-=p
        if p//20<self._people:
            self._starved=self._people-p//20
            self._people-=self._starved
        if plant>self._acres:
            raise GameException("You cannot plant more acres than you have!")
        
        if self._grain-plant<0:
            raise GameException("not enough minerals to plant!")
        self._acres=plant
        self._grain-=plant
        
        
        
        
        
        
        
        
class GameException(Exception):
    def __init__(self,msg):
        self._msg=msg
        
    @property
    def message(self):
        return self._msg