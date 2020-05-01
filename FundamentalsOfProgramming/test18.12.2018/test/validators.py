
'''
validators for id, name, attend and grade
'''

def idv(l,id):
    l=l.get_all()
    l=l.get_all()
    for i in range (0,len(l)):
        if l[i].id()==id:
            return False
        
    return True

def namev(name):
    l=name.split(' ')
    if len(l)<2:
        return False
    
    if len(l[0])<3:
        return False
    
    if len(l[1])<3:
        return False
    
def attendv(attend):
    if attend>=0:
        return True
    else:
        return False
    
def gradev(grade):
    if grade>0 and grade<=10:
        return True
    else:
        return False
    
    
def test():
    pass