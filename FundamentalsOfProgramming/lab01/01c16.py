#this function is calculating the sum of its proper divisors
def divsum(n):
    s=0
    for i in range(1,n-1):
        if n%i==0:
            s+=i
    return s
#this function is finding the largest perfect number smaller than a given number
def perfectnumber(n):
    i=n-1
    while i>1:
        if divsum(i)==i:
            return i
        else:
            i-=1
    return 0
n=int(input("enter a number "))
if perfectnumber(n)==0:
    print("the required number does not exist")
else:
    print(perfectnumber(n))

    
    
