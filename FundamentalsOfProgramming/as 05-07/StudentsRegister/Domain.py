class student:
    def __init__(self,id,name):
        self.id=id
        self.name=name
    def __str__(self):
        return str(self.id)+'.'+str(self.name)
    def get_id(self):
        return self.id
    def get_name(self):
        return self.name
    def set_id(self,id):
        self.id=id
    def set_name(self,name):
        self.name=name
class discipline:
    def __init__(self,id,name):
        self.id=id
        self.name=name
    def __str__(self):
        return str(self.id)+'.'+str(self.name)
    def get_id(self):
        return self.id
    def get_name(self):
        return self.name
    def set_id(self,id):
        self.id=id
    def set_name(self,name):
        self.name=name   
class grade:
    def __init__(self,disciplineid,studentid,grade):
        self.disciplineid=disciplineid
        self.studentid=studentid
        self.grade=[grade]
    def __str__(self):
        return 'disciplineID: '+str(self.disciplineid)+'/'+'studentID: '+str(self.studentid)+'/'+'grade: '+str(self.grade)
    def get_discid(self):
        return self.disciplineid
    def get_studid(self):
        return self.studentid
    def get_grade(self):
        return self.grade
    def set_discid(self,disiciplineid):
        self.disciplineid=disciplineid
    def set_studid(self,studentid):
        self.studentid=studentid
    def set_grade(self,grade):
        self.grade=grade     
def testStudent():
    s=student(133,'Alexa Andreas')
    assert s.get_id()==133
    assert s.get_name()=='Alexa Andreas'
    assert str(s)=='133.Alexa Andreas'
def testDiscipline():
    d=discipline(1,'CS')
    assert d.get_id()==1
    assert d.get_name()=='CS'
    assert str(d)=='1.CS'
def testGrade():
    g=grade(1,1,10)
    assert g.get_discid()==1
    assert g.get_studid()==1
    assert g.get_grade()==[10]
testStudent()
testDiscipline()
testGrade()