from math import sqrt
from copy import *
#Basic functions(get,set,read,print)
def getrealpart(complexnmb):
    return complexnmb[0]
def getimpart(complexnmb):
    return complexnmb[1]
def setrealpart(complexnmb, realpart):
    complexnmb[0]=realpart
def setimpart(complexnmb, impart):
    complexnmb[1]=impart
def createcomplexnmb(realpart, impart):
    return [
        realpart,
        impart
        ]
def modulus(a,b):
    return sqrt(a*a+b*b)
def printc(complexnmb):
    if getimpart(complexnmb)<0:
        print(getrealpart(complexnmb),'-',-getimpart(complexnmb),'i')
    else:
        print(getrealpart(complexnmb),'+',getimpart(complexnmb),'i')
def readcommand():
    raw_input=input()
    command=raw_input.split(' ')[0]
    param=raw_input.split(' ')[1:]
    return (command, param)
'''
converts a complex number from string to an integer
'''
def stoint(string):
    if string[0][0]=='-':
        if string[0][2]=='-':
            x=-int(string[0][1])
            y=-int(string[0][3])
        else:
            x=-int(string[0][1])
            y=int(string[0][3])
    elif string[0][1]=='-':
        x=int(string[0][0])
        y=-int(string[0][2])
    else:
        x=int(string[0][0])
        y=int(string[0][2])
    return x,y
def stointr(string):
    if string[2][0]=='-':
        if string[2][2]=='-':
            x=-int(string[2][1])
            y=-int(string[2][3])
        else:
            x=-int(string[2][1])
            y=int(string[2][3])
    elif string[2][1]=='-':
        x=int(string[2][0])
        y=-int(string[2][2])
    else:
        x=int(string[2][0])
        y=int(string[2][2])
    return x,y
def helpmenu():
    print("add <number>")
    print("insert <number> at <position>")
    print("remove <position>")
    print("remove <start position> to <end position>")
    print("replace <old number> with <new number>")
    print("list")
    print("list real <start position> to <end position>")
    print("list modulo [<|=|>] <number>")
    print("sum <start position> to <end position>")
    print("product <start position> to <end position>")
    print("fitler real")
    print("filter modulo [<|=|>]<number>")
    print("undo")
    print("exit")
#Functions that add numbers to the list
'''
adds a number to the list
'''
def add(complexnmb,userinput):
    x,y=stoint(userinput[1])
    complexnmb.append(createcomplexnmb(x,y))
'''
inserts a number at a given position in the list
'''
def insert(complexnmb,userinput):
    index=int(userinput[1][2])
    x,y=stoint(userinput[1])
    complexnmb.insert(index,createcomplexnmb(x,y))
#Functions that modify elements from the list
'''
removes a number from a given position
'''
def remove(complexnmb,userinput):
    del complexnmb[int(userinput[1][0])]
'''
removes all numbers between a start position and an end postition
'''
def removextoy(complexnmb,userinput):
   x=int(userinput[1][0])
   y=int(userinput[1][2])
   for i in range(x,y+1):
       del complexnmb[x]
'''
replaces a given number with another one
'''
def replace(complexnmb,userinput):
    xo,yo=stoint(userinput[1])
    xn,yn=stointr(userinput[1])
    replaceset(complexnmb,xo,yo,xn,yn)

def replaceset(complexnmb,xo,yo,xn,yn):
    for i in range(0,len(complexnmb)):
        if getrealpart(complexnmb[i])==xo and getimpart(complexnmb[i])==yo:
            setrealpart(complexnmb[i],xn)
            setimpart(complexnmb[i],yn)
    
#Functions that write numbers having different properties
'''
prints a list of numbers
'''
def shownumbers(list):
    for complexnmb in list:
        if getimpart(complexnmb)<0:
            print(getrealpart(complexnmb),'-',-getimpart(complexnmb),'i')
        else:
            print(getrealpart(complexnmb),'+',getimpart(complexnmb),'i')    

'''
prints all real numbers between a start position and an end postition
'''
def showrealnumbersxtoy(complexnmb,userinput):
    x=int(userinput[1][1])
    y=int(userinput[1][3])
    copy=showrealp(complexnmb,x,y)
    shownumbers(copy)

def showrealp(complexnmb,x,y):
    copy=[]
    for i in range(x,y+1):
        if getimpart(complexnmb[i])==0:
            copy.append(createcomplexnmb(getrealpart(complexnmb[i]),getimpart(complexnmb[i])))
    return copy
'''
writes all numbers having a smaller modulus than a given x
'''
def mod1(complexnmb,userinput):
    x=int(userinput[1][2])
    if userinput[0]=='list':
        for i in range(0,len(complexnmb)):
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))<x:
                printc(complexnmb[i])
    else:
        y=len(complexnmb)
        i=0
        while i<y:
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))>x:
                del complexnmb[i]
                y-=1
            else:
                i+=1        
               
'''
writes all numbers having an equal modulus to x
'''
def mod2(complexnmb,userinput):
    x=int(userinput[1][2])
    if userinput[0]=='list':
        for i in range(0,len(complexnmb)):
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))==x:
                printc(complexnmb[i])
    else:
        y=len(complexnmb)
        i=0
        while i<y:
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))==x:
                del complexnmb[i]
                y-=1
            else:
                i+=1        
     
'''
writes all numbers having a bigger modulus than a given x
'''            
def mod3(complexnmb,userinput):
    x=int(userinput[1][2])
    if userinput[0]=='list':
        for i in range(0,len(complexnmb)):
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))>x:
                printc(complexnmb[i])
    else:
        y=len(complexnmb)
        i=0
        while i<y:
            if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))<x:
                del complexnmb[i]
                y-=1
            else:
                i+=1        
     
'''
calls the mod1, mod2 and mod3 depending on the given symbol
'''
def mod(complexnmb,userinput):
    symbol=userinput[1][1]
    if(symbol=='>'):
        mod3(complexnmb,userinput)
    elif(symbol=='='):
        mod2(complexnmb,userinput)
    elif(symbol=='<'):
        mod1(complexnmb,userinput)

#obtains different characteristics of sub-lists
def sum(complexnmb,userinput):
    x=int(userinput[1][0])
    y=int(userinput[1][2])
    s=[]
    s.append(0)
    s.append(0)
    for i in range(x,y+1):
        s[0]+=getrealpart(complexnmb[i])
        s[1]+=getimpart(complexnmb[i])
    printc(s)
def product(complexnmb,userinput):
    x=int(userinput[1][0])
    y=int(userinput[1][2])
    p=[]
    p.append(getrealpart(complexnmb[x]))
    p.append(getimpart(complexnmb[x]))
    for i in range(x+1,y+1):
        a=p[0]
        p[0]=getrealpart(complexnmb[i])*p[0]-p[1]*getimpart(complexnmb[i])
        p[1]=getimpart(complexnmb[i])*a+getrealpart(complexnmb[i])*p[1]
    printc(p)
'''
filters the list
'''
def filterr(complexnmb):
    x=len(complexnmb)
    i=0
    while i<x:
        if getimpart(complexnmb[i])==0:
            del complexnmb[i]
            x-=1
        else:
            i+=1

#Main program
def start():
    complexnmb=[[42,0],[1,-6],[2,1],[2,2],[3,4],[4,-10],[3,8],[-1,0],[-4,-9],[0,5]]
    undolist=[]
    symbols={'<':mod1,'=':mod2,'>':mod3}
    print("Remember you can always type help for a list of commands")
    while True:
        userinput=readcommand()
        if userinput[0]=='add' and len(userinput[1])==1:
            undolist.append(complexnmb[:])
            add(complexnmb,userinput)
        elif userinput[0]=='insert' and len(userinput[1])==3:
            undolist.append(complexnmb[:])
            insert(complexnmb,userinput)
        elif userinput[0]=='remove':
            if len(userinput[1])==3 and int(userinput[1][2])<len(complexnmb):
                undolist.append(complexnmb[:])
                removextoy(complexnmb,userinput)
            elif len(userinput[1])==1:
                undolist.append(complexnmb[:])
                remove(complexnmb,userinput)
            else:
                print("wrong input")
        elif userinput[0]=='list':
            if len(userinput[1])==4 and userinput[1][0]=='real' and userinput[1][2]=='to' and int(userinput[1][3])<=len(complexnmb):
                showrealnumbersxtoy(complexnmb,userinput)
            elif len(userinput[1])==3 and userinput[1][0]=='modulo'and userinput[1][1] in symbols.keys():
                mod(complexnmb,userinput)
            elif len(userinput[1])==0:
                shownumbers(complexnmb)
            else:
                print("wrong input")
        elif userinput[0]=='replace' and userinput[1][1]=='with' and len(userinput[1])==3:
            undolist.append(complexnmb[:])
            replace(complexnmb,userinput)
        elif userinput[0]=='exit':
            return
        elif userinput[0]=='help':
            helpmenu();
        elif userinput[0]=='sum' and len(userinput[1])==3 and int(userinput[1][2])<len(complexnmb):
            sum(complexnmb,userinput)
        elif userinput[0]=='product'and len(userinput[1])==3 and int(userinput[1][2])<len(complexnmb):
            product(complexnmb,userinput)
        elif userinput[0]=='filter':
            if userinput[1][0]=='modulo' and len(userinput[1])==3 and userinput[1][1] in symbols.keys():
                undolist.append(complexnmb[:])
                mod(complexnmb,userinput)
            elif userinput[1][0]=='real':
                undolist.append(complexnmb[:])
                filterr(complexnmb)
            else:
                print('wrong input')
        elif userinput[0]=='undo':
            if len(undolist)==0:
                print('no more undos for you')
            else:
                complexnmb=undolist[len(undolist)-1]
                del undolist[len(undolist)-1]
        else:
            print("wrong input")
start()

