from FUNctions import *
from Domain import *
from Repository import *
class ui:
     #startingmethod
    def showmenu():
        print('1-add student')
        print('2-remove student')
        print('3-update student id')
        print('4-update student name')
        print('5-list of student')
        print('6-add discipline')
        print('7-remove discipline')
        print('8-update discipline id')
        print('9-update discipline name')
        print('10-list discipline')
        print('11-grade a student')
        print('12-list of grades')
        print('13-exit')
    #startingmethod
    def menu():   
        #studlist=[student(1,'Marcus Joyce'),student(2,'Alexa Andreas'),student(3,'Casper Ghost'),student(4,'Leila Ay'),student(5,'Antonio Benson'),student(6, 'Hunter Bar'),student(7,'Lily Duran'),student(8, 'Lisa Ritter'),student(9,'Ashley Scott'),student(10,'Tyler Lutz')]
        disclist=[discipline(1,'mate'),discipline(2,'cs'),discipline(3,'logic'),discipline(4,'asc'),discipline(5,'fp')]
        gradelist=[grade(1,2,10),grade(2,5,6),grade(4,7,8),grade(2,1,9)]
        studlist=StudentRepository()
        while True:
            ui.showmenu()
            user_input=input()
            if user_input=='1':
                id=int(input("Give me the id of the student: "))
                name=input("Give me the name of the student: ")
                while validstud(studlist, id)==False:
                    id=int(input("Give me a valid id: "))
                studlist.add(student(id,name))
            elif user_input=='2':
                id=int(input("Give me the id of the student you want to delete: "))
                removeStud(id, studlist)
                #deletegrade(gradelist, id)
            elif user_input=='3':
                id=int(input("Give me the id you want to replace: "))
                new_id=int(input("Give me the new id: "))
                d=studlist.get_all()
                name=d[id].name
                studlist.add(student(new_id,name))
                removeStud(id, studlist)
            elif user_input=='4':
                name=input("Give me a new name: ")
                id=int(input("Give me the id of the student: "))
                d=studlist.get_all()
                d[id]=student(id,name)
            elif user_input=='5':
                list(studlist)
                print()
            elif user_input=='6':
                id=int(input("Give me the id of the discipline: "))
                name=input("Give me the name of the discipline: ")
                while validdisc(disclist, id)==0:
                    id=int(input("Give me a valid id: "))
                addDisc(id, name, disclist)
            elif user_input=='7':
                pos=int(input("Give me the position of the discipline you want to delete: "))
                id=disclist[pos].get_id()
                removeDisc(pos, disclist)
                deletegradedisc(gradelist, id)
            elif user_input=='8':
                id=int(input("Give me a new id: "))
                pos=int(input("Give me the position of the discipline: "))
                disclist[pos].id=id
            elif user_input=='9':
                name=input("Give me a new name: ")
                pos=int(input("Give me the position of the discipline: "))
                disclist[pos].name=name
            elif user_input=='10':
                list(disclist)
                print()
            elif user_input=='11':
                grd=int(input("Give me the student grade: "))
                studentid=int(input("Give me the student id: "))
                discid=int(input("Give me the discipline id: "))
                if findsandd(gradelist,studentid,discid,grd)==0:
                    mark(gradelist,discid,studentid,grd)
            elif user_input=='12':
                list(gradelist)
                print()
            elif user_input=='13':
                return
            else:
                print('Invalid input')
        
ui.menu()