from test.domain import student

class StudentControler():
    def __init__(self,repo):
        self.repo=repo
        
    def store(self,id,name,attend,grade):
        s=student(id,name,attend,grade)
        self.repo.store(s)
        
    def get_all(self):
        return self.repo
    
    def __len__(self):
        return len(self.repo)
    
    def __str__(self):
        return str(self.repo)