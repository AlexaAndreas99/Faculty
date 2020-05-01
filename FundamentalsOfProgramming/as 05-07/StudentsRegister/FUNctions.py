from Domain import *
from turtledemo.minimal_hanoi import Disc
#from ui import *

def addStud(id,name,studlist):
    studlist.append(student(id,name))
    
def removeStud(id,studlist):
    d=studlist.get_all()
    del d[id]
def list(list):
    d=list.get_all()
    for i in d:
        print(d[i])

def addDisc(id,name,disclist):
    disclist.append(discipline(id,name))
    
def removeDisc(pos,disclist):
    del disclist[pos]
def mark(gradelist,discid,studentid,grd):
    gradelist.append(grade(discid,studentid,grd))
def deletegrade(gradelist,id):
    i=0
    while i<len(gradelist):
        if gradelist[i].get_studid()==id:
            del gradelist[i]
        else:
            i+=1
def deletegradedisc(gradelist,id):
    i=0
    while i<len(gradelist):
        if gradelist[i].get_discid()==id:
            del gradelist[i]
        else:
            i+=1
def test(studlist,disclist,gradelist):
    pass
def validstud(studlist,id):
    d=studlist.get_all()
    for i in d :
        if d[i].id==id:
            return False
    return True
def validdisc(disclist,id):
    for i in range(0,len(disclist)):
        if disclist[i].id==id:
            return 0
    return 1
def findsandd(gradelist,studid,discid,grd):
    for i in range(0,len(gradelist)):
        if gradelist[i].studentid==studid and gradelist[i].disciplineid==discid:
            aux=gradelist[i].grade
            aux.append(grd)
            gradelist[i].grade=aux
            return 1
    return 0
            
