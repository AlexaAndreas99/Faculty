from Domain import *

class StudentRepository():
    def __init__(self):
        self.repo={}
    def add(self,student):
        self.repo[student.get_id()]=student
    def get_all(self):
        return self.repo
    def __str__(self):
        return str(self.repo)
def testadd():
    repo=StudentRepository()
    s1=student(1,'Alexa Andreas')
    repo.add(s1)
    d=repo.get_all()
    assert len(d)==1
    assert str(d[1].name)=="Alexa Andreas"
    assert d[1].id==1
testadd()

class DisciplineRepository():
    def __init__(self):
        self.repo={}
    def add(self,discipline):
        self.repo[discipline.get_id()]=discipline
    def get_all(self):
        return self.repo
    def __str__(self):
        return str(self.repo)   
    
class GradeRepository():
    def __init__(self):
        self.repo={}
    def add(self,student):
        self.repo[student.get_id()]=student
    def get_all(self):
        return self.repo
    def __str__(self):
        return str(self.repo)