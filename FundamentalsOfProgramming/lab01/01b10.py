#this function is calculating the product of all the proper factors of n
def product(n):
    p=1
    for i in range(2,n-1):
            if n%i==0:
                p*=i
    
    return p
n=int(input("enter a number "))
print(product(n))
            
            
