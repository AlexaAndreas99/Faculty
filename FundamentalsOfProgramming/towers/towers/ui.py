from towers.textfile import textfileroom, textfileres

'''
roomrepo=textfileroom('rooms.txt')
l=roomrepo.get_all()
for i in l:
    print(i)
'''
from towers.domain import reservation
import random
from towers.repository import repository
def print1():
    print("1.create a reservation")
    print('0.exit')
def start():
    repo=textfileres()
    r=reservation(1234,1,'asd',3,'15.02','19.02')
    repo.store(r)
    roomrepo=textfileroom('rooms.txt')
    while True:
        print1()
        user_input=input()
        if user_input=='2':
            name=input("family name: ")
            roomtype=int(input("room type: "))
            guests=int(input("guests:"))
            l=roomrepo.get_all()
            reserv=repo.get_all()
            
            n=random.randint(1000,9999)
            n=1234
            if n==reserv[0].get_id():
                print(n)
                
            for i in l:
                if int(i.get_type())==roomtype:
                    print(i)
            try:
                r=reservation(1234,1,name,guests,'15.02','19.02')
            except ValueError:
                print("the reservation is invalid ")
                
        elif user_input=='0':
            return
        if user_input=='1':
            l=repo.get_all()
            for i in l:
                print(i)
        
start()