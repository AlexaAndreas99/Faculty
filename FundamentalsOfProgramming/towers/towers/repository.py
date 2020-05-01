class repository():
    def __init__(self):
        self._repo=[]
    
    def store(self,object):
        self._repo.append(object)
    def get_all(self):
        return self._repo
    def delete(self,id):
        pass