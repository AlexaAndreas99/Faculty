class Repository():
    def __init__(self):
        self._repo=[]
        
    def store(self,obj):
        self._repo.append(obj)
    
    def get_all(self):
        return self._repo
    
    def __str__(self):
        return str(self._repo)
    
    def __len__(self):
        return len(self._repo)