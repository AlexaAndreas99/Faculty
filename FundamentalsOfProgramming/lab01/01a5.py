#this function is verifying if anumber is prime
def prime_(a):
    if(a<2):
        return 0
    for i in range(2,a-1):
        if a%i==0:
            return 0
    return 1
#this function finds the largest prime number than a given one
def pn(n):
    i=n-1
    if n==2:
        return 0
        
    while i>=2: 
        if prime_(i)==1:
            return i
        i-=1
n=int(input("enter a number "))
if pn(n)==0:
    print("the required number does not exist")
else:
    print(pn(n))
