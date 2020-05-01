
'''
function for giving the bonus b for students with the minimum presence p
'''
'''
def give_bonus(l,p,b):
    l=l.get_all()
    l=l.get_all()
    for i in range(0,len(l)):
        if int(l[i].attend())>=p:
            if l[i].grade()+b>10:
                #l[i].set_grade()=10
            #else:
            #    l[i].set_grade=l[i].grade()+b
'''