

l=[0,1,2,3,4,5,6,7,8,9]
d=2
#print(type(l))
#print(type(d))
def sum(l):
    k=[]
    s=0
    if type(l)!=type(k):
        raise TypeError()
    
    for i in range(len(l)):
        if l[i]%2==0:
            s+=l[i]
        
    if s==0:
        raise ValueError
    return s
'''
try:
    try:
        k=sum(l)
    except TypeError:
        print("not list")
except ValueError:
    print("no")
'''
#print(l[4:])
def f(n):
    d=2
    while d<n-1 and n%d>0:
        d+=1
    return d>=n-1

s=int(input())
print(s)