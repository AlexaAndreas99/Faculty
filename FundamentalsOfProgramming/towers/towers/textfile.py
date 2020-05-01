from towers.domain import room, reservation
from towers.repository import repository
class textfileroom():
    def __init__(self,file_name='rooms.txt'):
        self._repo=[]
        self._file_name=file_name
        self._loadfile()
    
    def _store(self,object):
        self._repo.append(object)
    
    def get_all(self):
        return self._repo
    
    def _loadfile(self):
        
        f=open(self._file_name,"r")
        line=f.readline()
        while(len(line))>2:
            tok=line.split(",")
            r=room(tok[0],tok[1].strip())
            self._store(r)
            line=f.readline()
        f.close()

class textfileres():
    def __init__(self,file_name='reservations.txt'):
        repository.__init__(self)
        self._file_name=file_name
        self._load()
    
    def store(self,object):
        repository.store(self,object)
        self._save()
    
    def get_all(self):
        return repository.get_all(self)
        
    def _load(self):
        f=open(self._file_name,"r")
        line=f.readline()
        while len(line)>2:
            tok=line.split(',')
            r=reservation(int(tok[0]),int(tok[1]),tok[2],int(tok[3]),tok[4],tok[5].strip())
            repository.store(self,r)
            line=f.readline()
        f.close()
        
    def _save(self):
        f=open(self._file_name,"w")
        l=repository.get_all(self)
        for i in l:
            s=(str(i.get_id())+','+str(i.get_room_nmb())+','+i.get_family()+','+str(i.get_guests())+','+i.get_arrival()+','+i.get_dep()+"\n")
            f.write(s)
        f.close()
            
            