from test.repository import Repository
from test.controller import StudentControler
from test.validators import *
from test.file import file
from test.functions import *

def list(l):
    l=l.get_all()
    l=l.get_all()
    for i in range(0,len(l)):
        print(l[i])
            
def show():
    print("0.exit")
    print("1.add student")
    print("2.show all students")
    print("3.give bonus")
    print("4.search for students ordered by name")
        
        
        
def ui():
    #srepo=Repository()
    srepo=file()
    stud_ctrl=StudentControler(srepo)
        
    while True:
        show()
        user_input=input()
        if user_input=='0':
            return
        if user_input=='1':
            
            id=int(input("id: "))
            while idv(stud_ctrl,id)==False:
                id=int(input("i ned a valid id: "))
            
            name=input("name: ")
            while namev(name)==False:
                name=input("i need a valid name: ")
            
            attend=int(input("attend: "))
            while attendv(attend)==False:
                attend=int(input("i need a valid attend: "))
            
            grade=int(input("grade: "))
            while gradev(grade)==False:
                grade=int(input("i need a valid grade: "))
            stud_ctrl.store(id,name,attend,grade)
        if user_input=='2':
            list(stud_ctrl)
        if user_input=='3':
            p=int(input("give me the minimum attendance: "))
            b=int(input("bonus: "))
            give_bonus(stud_ctrl,p,b)
            
            
ui()