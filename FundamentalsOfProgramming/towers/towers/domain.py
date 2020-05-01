class reservation():
    def __init__(self,id,room_nmb,family,guests,arrival,dep):
        if len(family)==0:
            raise ValueError
        if guests<1 or guests>4:
            raise ValueError
        

        self._id=id
        self._room_nmb=room_nmb
        self._family=family
        self._guests=guests
        self._arrival=arrival
        self._dep=dep
    
    def __str__(self):
        return str(self._id)+', '+str(self._room_nmb)+', '+str(self._family)+', '+str(self._guests)+', '+str(self._arrival)+','+str(self._dep)
    def get_id(self):
        return self._id
    def get_room_nmb(self):
        return self._room_nmb
    def get_family(self):
        return self._family
    def get_guests(self):
        return self._guests
    def get_arrival(self):
        return self._arrival
    def get_dep(self):
        return self._dep
    
    
    
class room():
    def __init__(self,number,type):
        self._number=number
        self._type=type
    def __str__(self):
        return str(self._number)+','+str(self._type)
    def get_number(self):
        return self._number
    def get_type(self):
        return self._type
    
r=reservation(1223,1,'Albu',2,'15.02','19.02')
r=room(1,2)
#print(r)
s='123'
w=int(s[1])*10+int(s[2])
#print(w)