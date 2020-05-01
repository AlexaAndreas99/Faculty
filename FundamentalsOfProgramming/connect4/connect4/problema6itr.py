
def solutionFound(x):
    
    rez=[]
    for i in range(len(x)):
        if x[i]==1:
            rez.append('(')
        else:
            rez.append(')')
    print(rez) 
    
    #print(x)

def valid(n,x):
    pd=0
    pi=0
    
    for i in range(0,n+1):
        print(x[i])
        s=x[i]
        if (s==1):
            pd+=1
        else:
            pi+=1
    if pi>pd or pd>n/2:
        return 0
    return 1

def backitr(n):
    x=[1]
    while len(x)>0:
        for i in range(1,3):
            x[len(x)-1]=i
            if valid(n,x[len(x)-1]):
                if len(x)==n:
                    solutionFound(x)
                else:
                    x.append(-1)
            else:
                x=x[:-1]
                    
backitr(2)