from test.repository import Repository
from test.domain import student

class file(Repository):
    def __init__(self,file_name="studentstest"):
        Repository.__init__(self)
        self._file_name=file_name
        self.load_file(file_name)
        
    def store(self, obj):
        Repository.store(self, obj)
        
    def load_file(self,file_name):
        f=open(file_name,"r")
        line=f.readline()
        while len(line)>2:
            tok=line.split(",")
            s=student(tok[0],tok[1],tok[2],tok[3].strip())
            self.store(s)
            line=f.readline()
        f.close()