from math import sqrt
def getrealpart(complexnmb):
    #return complexnmb['realpart']
    return complexnmb[0]
def getimpart(complexnmb):
    #return complexnmb['impart']
    return complexnmb[1]
def setrealpart(complexnmb, realpart):
    #complexnmb['realpart']=realpart
    complexnmb[0]=realpart
def setimpart(complexnmb, impart):
    #complexnmb['impart']=impart
    complexnmb[1]=impart
def createcomplexnmb(realpart, impart):
    '''
    return {
        'realpart' : realpart,
        'impart' : impart
        }
    '''
    return [
        realpart,
        impart
        ]
def showmenu():
    print("1- Read a complex number")
    print("2- Print the list of complex numbers")
    print("3- Print the longest sequence constiting of real numbers")
    print("4- Print the longest sequence constiting of numbers that have their modulus between 0 and 10")
    print("5-exit")
    
def shownumbers(list):
    for complexnmb in list:
        if getimpart(complexnmb)<0:
            print(getrealpart(complexnmb),'-',-getimpart(complexnmb),'i')
        else:
            print(getrealpart(complexnmb),'+',getimpart(complexnmb),'i')
        print()    
def setup(list):
    list.append(createcomplexnmb(-23,0))
    list.append(createcomplexnmb(13,0))
    list.append(createcomplexnmb(-1,3))
    list.append(createcomplexnmb(2,3))
    list.append(createcomplexnmb(12,0))
    list.append(createcomplexnmb(0,-0))
    list.append(createcomplexnmb(3,0))
    list.append(createcomplexnmb(4,3))
    list.append(createcomplexnmb(4,-3))
    list.append(createcomplexnmb(4,4))

def firstproperty(complexnmb):
    '''
the program is finding the longest sequence formed from real numbers and it's returning its length and the first and final position
'''
    k=0
    maxi=0
    xmax=0
    ymax=0
    x=0
    y=0
    for i in range(0,len(complexnmb)):
       if getimpart(complexnmb[i])==0:
           k+=1
           y+=1
       else:
           if k>maxi:
               maxi=k
               ymax=y-1
               xmax=x
           x=i+1
           y+=1
           k=0
    if k>maxi:
        maxi=k
        ymax=y
        xmax=x
    if ymax==len(complexnmb):
        return maxi,xmax,ymax-1
    else:
        return maxi,xmax,ymax
'''
the program is printing a sequence of numbers
'''    
def printseq(complexnmb,x,y):
    for i in range (x,y+1):
        if getimpart(complexnmb[i])<0:
            print(getrealpart(complexnmb[i]),'-',-getimpart(complexnmb[i]),'i')
        else:
            print(getrealpart(complexnmb[i]),'+',getimpart(complexnmb[i]),'i')   
def modulus(a,b):
    '''
the program is calculating the modulus of a complex number
'''
    return sqrt(a*a+b*b)
'''
the program is finding the longest sequence where the modulus of each number is between 0 and 10
'''

def secondproperty(complexnmb):
    k=0
    maxi=0
    xmax=0
    ymax=0
    x=0
    y=0
    for i in range(0,len(complexnmb)):
       if modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))>=0 and modulus(getrealpart(complexnmb[i]),getimpart(complexnmb[i]))<=10: 
           k+=1
           y+=1
       else:
           if k>maxi:
               maxi=k
               ymax=y-1
               xmax=x
           x=i+1
           y+=1
           k=0
    if k>maxi:
        maxi=k
        ymax=y
        xmax=x
    if ymax==len(complexnmb):
        return maxi,xmax,ymax-1
    else:
        return maxi,xmax,ymax    

def main():
    complexnmb=[]
    setup(complexnmb)
    while True:
        showmenu()
        a= int(input())
        
        if a==1:
            complexnmb.append(createcomplexnmb(int(input("Enter the real part of a complex number ")),int(input("Enter the imaginary part of a complex number "))))
        elif a==2:
            shownumbers(complexnmb)
        elif a==3:
            maxi,x,y=firstproperty(complexnmb)
            print(maxi)
            print(printseq(complexnmb,x,y))
        elif a==4:
            maxi,x,y=secondproperty(complexnmb)
            print(maxi)
            print(printseq(complexnmb,x,y))
        elif a==5:
            return
        else:
            print("invalid input.")
            

main()
