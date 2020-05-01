'''
student
'''
class student():
    def __init__(self,id,name,attend,grade):
        self._id=id
        self._name=name
        self._attend=attend
        self._grade=grade
        
    def __str__(self):
        return (str(self._id)+','+self._name+','+str(self._attend)+','+str(self._grade))
    
    def id(self):
        return self._id
    
    def name(self):
        return self._name
    def attend(self):
        return self._attend
    def grade(self):
        return int(self._grade)
    
    def set_grade(self,grd):
        self._grade=grd
    
    #def sum(self,nmb):
    #    return int(self._grade+nmb)
    
    def __eq__(self):
        pass
    def __sum__(self,nmb):
        return self._grade+nmb