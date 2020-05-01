# -*- coding: utf-8 -*-
"""
Created on Sun Mar  8 14:21:16 2020

@author: Andreas-PC
"""
import copy as cp
import qtpy as qt

class State:
    def __init__(self,n):
        self.__board=[]
        self.__N=n
        self.__currentn=0
        for i in range(n):
            self.__board.append(0)
    
    def __str__(self):
        return self.__board.__str__()
    
    def setValues(self,values):
        self.__board=values[:]
        
    def getSize(self):
        return self.__N
    
    def getValues(self):
        return self.__board[:]
    
    def isGoal(self):
        if self.__currentn==self.__N:
            return True
        else:
            return False
    
    def isSafe(self,clm):
        for i in range(0,self.__currentn):
            if self.__board[i]==clm or abs(clm-self.__board[i]) == self.__currentn-i:
                return False
        return True
    
    def place(self, clm):
        if clm>=0 and clm < self.__N:
            self.__board[self.__currentn]=clm
            self.__currentn+=1
   
    def unPlace(self):
        if(self.__currentn>0):
            self.__currentn-=1

class Problem:
    def __init__(self,n):
        self.__state=State(n)
        
    def getRoot(self):
        return self.__state
    
    

class Controller:
    def __init__(self,problem):
        self.__problem=problem

    def dfs(self, problem):

        if problem.getRoot().isGoal() == True:
            return problem.getRoot()
        else:
            for i in range(problem.getRoot().getSize()):
                
                if problem.getRoot().isSafe(i):
                    problem.getRoot().place(i)
                    res=self.dfs(problem)
                    if res != None:
                        return res
                    problem.getRoot().unPlace()
        return None        
                    
        
        
        
    def greedy(self,Problem):
        n=self.__problem.getRoot().getSize()
        r=[0 for i in range(n)]
        board=[cp.deepcopy(r) for i in range(n)]        
        for i in range(n):
            for j in range(n):
                if board[i][j]==0:
                    for k in range(0,j):
                        board[i][k]=-1
                    for k in range(j+1,n):
                        board[i][k]=-1
                    for k in range(0,i):
                        board[k][j]=-1
                    for k in range(i+1,n):
                        board[k][j]=-1
                    o=cp.deepcopy(i)
                    p=cp.deepcopy(j)
                    while o>0 and p>0:
                        board[o][p]=-1
                        o-=1
                        p-=1
                    o=cp.deepcopy(i)
                    p=cp.deepcopy(j)
                    while o<n and p<n:
                        board[o][p]=-1
                        o+=1
                        p+=1
                    
                    o=cp.deepcopy(i)
                    p=cp.deepcopy(j)
                    while o>0 and p<n:
                        board[o][p]=-1
                        o-=1
                        p+=1
                    o=cp.deepcopy(i)
                    p=cp.deepcopy(j)
                    while o<n and p>0:
                        board[o][p]=-1
                        o+=1
                        p-=1
                    board[i][j]=1
        
        for i in range(n):
            for j in range(n):
                if board[i][j]==-1:
                    board[i][j]=0
        return board
class UI:
    def __init__(self,n):
        self.__problem=Problem(n)
        self.__ctrl=Controller(self.__problem)
        
    def mainMenu():
        pass
    
    def printDFS(self):
        print(self.__ctrl.dfs(self.__problem),'\n')
        n=self.__problem.getRoot().getSize()
        board = self.__problem.getRoot().getValues()
        r=[0 for i in range(n)]
        m=[cp.deepcopy(r) for i in range(n)]
        for i in range(n):
            m[i][board[i]]=1
                
        for i in m:
            print (i)
    def printGreedy(self):
        for i in self.__ctrl.greedy(self.__problem):
            print (i)

def main():
    while True:
        print("0.Exit\n1.DFS\n2.Greedy")
        i=int(input())
        n=int(input("Size: "))
        ui=UI(n)

        if i==1:
            ui.printDFS()
        elif i==2:
            ui.printGreedy()
        else: 
            return
main()
print("Hello World!")
