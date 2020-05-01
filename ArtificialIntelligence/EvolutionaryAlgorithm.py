# -*- coding: utf-8 -*-
"""
Created on Wed Mar 25 11:59:23 2020

@author: Andreas-PC
"""
from random import randint, random
from copy import deepcopy
import threading
from math import sqrt
import matplotlib.pyplot as plt


###############################################################################################################

class EA:
    '''
    Representation: a matrix with a tuple (x,y) on every position
    '''
    def individual(self,length):
        ind=[]
        for i in range(length):
            l=[]
            for j in range(length):
                t=(randint(1,length),randint(1,length))
                l.append(t)
            ind.append(l)
        return ind
    
    def population(self,count, lenght):
        return [self.individual(lenght) for x in range(count)]    
        
    def fitness(self,individual):
        '''
        0-best
        (length+length)*2-worst
        for every row or column that is wrong add 1 to f
        '''
        
        f=0
        length= len(individual)
        #visit rows
        for i in individual:
            isum=0
            jsum=0
            for j in i:
                isum+=j[0]
                jsum+=j[1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        
        #visit columns
        for j in range(length):
            isum=0
            jsum=0
            for i in range(length):
                isum+=individual[i][j][0]
                jsum+=individual[i][j][1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        return f
    
    def mutate(self,individual,pM):
        if(pM>random()):
            n=len(individual)
            i=randint(0,n-1)
            j=randint(0,n-1)
            t=(randint(1,n),randint(1,n))
            individual[i][j]=t
        return individual
        
    def crossover(self,parent1, parent2):
        n=len(parent1)
        child=[]
        i=randint(0,int(n/2))
        for i1 in range(i):
            child.append(parent1[i1])
        
        for i2 in range(i,n):
            child.append(parent2[i2])
        return child
        
    def iteration(self,pop, pM):
        i1=randint(0,len(pop)-1)
        i2=randint(0,len(pop)-1)
        if(i1!=i2):
            c=self.crossover(pop[i1],pop[i2])
            c=self.mutate(c,pM)
            f1=self.fitness(pop[i1])
            f2=self.fitness(pop[i2])
            
            fc=self.fitness(c)
            if(f1>f2) and (f1>fc):
                pop[i1]=c
            if(f2>f1) and (f2>fc):
                pop[i2]=c
        return pop
    
    def eaMain(self,noIt,dP,dI,prob):
        dimPopulation = dP
        dimIndividual = dI
        pM=prob
        noIteratii=noIt
        
        P = self.population(dimPopulation, dimIndividual)
        for i in range(noIteratii+1):
            P=self.iteration(P,pM)
            if(i%1000==0):
                graded = [(self.fitness(x),x) for x in P]
                graded = sorted(graded)
                result = graded[0]
                fitnessOptim=result[0]
                individualOptim=result[1]
                print('Result: The best individual after ',i,' iterations is: ')
                for i in individualOptim:
                    print(i)
                print('with the fitness: ',fitnessOptim)
        return fitnessOptim

###############################################################################################################

class HillClimb:
    def generate_random_solution(self,length):
        ind=[]
        for i in range(length):
            l=[]
            for j in range(length):
                t=(randint(1,length),randint(1,length))
                l.append(t)
            ind.append(l)
        return ind
    
    def evaluate(self,solution):
        '''
        0-best
        (length+length)*2-worst
        for every row or column that is wrong add 1 to f
        '''
        f=0
        length= len(solution)
        #visit rows
        for i in solution:
            isum=0
            jsum=0
            for j in i:
                isum+=j[0]
                jsum+=j[1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        
        #visit columns
        for j in range(length):
            isum=0
            jsum=0
            for i in range(length):
                isum+=solution[i][j][0]
                jsum+=solution[i][j][1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        return f
    
    def mutate_solution(self,solution):
       #mutate a random row
        n = len(solution)
        i = randint(0,n-1)
        l=[]
        for j in range(n):
            t=(randint(1,n),randint(1,n))
            l.append(t)
        solution[i]=deepcopy(l)
        return solution
    
    def hcMain(self,dimI):
        
        best = self.generate_random_solution(dimI)
        bestScore = self.evaluate(best)
        i=-1
        while True:
            i+=1
            if i%10000==0:
                print('Best score so far after ',i,' iterations is', bestScore, 'Solution: ')
                for j in best:
                    print(j)
            
            if bestScore == 0 or i == 100000:
                break
            newSolution=deepcopy(best)
            self.mutate_solution(newSolution)
            newScore = self.evaluate(newSolution)
            if newScore < bestScore:
                best = deepcopy(newSolution)
                bestScore = deepcopy(newScore)
        print('Best score so far after ',i,' iterations is', bestScore, 'Solution: ')
        for j in best:
            print(j)
###############################################################################################################

class particle:
    def __init__(self, l):
        self._position = self.createPosition(l)
        self.evaluate()
        self.velocity = [0 for i in range(l)]
        
        self._bestPosition = self._position.copy()
        self._bestFitness = self._fitness
        
    def createPosition(self, length):
        ind=[]
        for i in range(length):
            l=[]
            for j in range(length):
                t=(randint(1,length),randint(1,length))
                l.append(t)
            ind.append(l)
        return ind
    
    def fit(self,position):
        '''
        0-best
        (length+length)*2-worst
        for every row or column that is wrong add 1 to f
        '''
        f=0
        length= len(position)
        #visit rows
        for i in position:
            isum=0
            jsum=0
            for j in i:
                isum+=j[0]
                jsum+=j[1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        
        #visit columns
        for j in range(length):
            isum=0
            jsum=0
            for i in range(length):
                isum+=position[i][j][0]
                jsum+=position[i][j][1]
            if(isum!=(length*(length+1))/2):
                f+=1
            if(jsum!=(length*(length+1))/2):
                f+=1
        return f
    
    def evaluate(self):
        self._fitness = self.fit(self._position)
        
    @property
    def position(self):
        return self._position
    @property
    def fitness(self):
        return self._fitness
    @property
    def bestPosition(self):
        return self._bestPosition
    @property
    def bestFitness(self):
        return self._bestFitness
    @position.setter
    def position(self, newPosition):
        self._position = newPosition.copy()
        self.evaluate()
        if(self._fitness < self.bestFitness):
            self._bestPosition = self._position
            self._bestFitness = self._fitness


class PSO:
    def population(self,count, l):
        return [particle(l) for i in range(count)]
    
    def selectNeighbours(self,pop,nSize):
        
        if nSize > len(pop):
            nSize = len(pop)
        neighbours=[]
        for i in range(len(pop)):
            localNeigh = []
            for j in range(nSize):
                x = randint(0, len(pop)-1)
                while x in localNeigh:
                    x=randint(0, len(pop)-1)
                localNeigh.append(x)
            neighbours.append(deepcopy(localNeigh))
        return neighbours
    
    def iteration(self,pop, neighbours,c1,c2,w):
        
        bestNeighbours = []
        for i in range(len(pop)):
            bestNeighbours.append(neighbours[i][0])
            for j in range(1,len(neighbours[i])):
                if pop[bestNeighbours[i]].fitness > pop[neighbours[i][j]].fitness:
                    bestNeighbours[i] = neighbours[i][j]
                    
        for i in range(len(pop)):
            for j in range(len(pop[0].velocity)):
                newVelocity = w*pop[i].velocity[j]
                newVelocity = newVelocity + c1*random()*(pop[bestNeighbours[i]].position[j][randint(0,1)][randint(0,1)]-pop[i].position[j][randint(0,1)][randint(0,1)])
                newVelocity = newVelocity + c2*random()*(pop[i].bestPosition[j][randint(0,1)][randint(0,1)]-pop[i].position[j][randint(0,1)][randint(0,1)])
                pop[i].velocity[j] = newVelocity
        
        return pop
    
    def psoMain(self,noPart,dimP,noIteratii=100):
        
        noParticles = noPart
        dimParticle = dimP
        
        w=1.0
        c1=1.
        c2=2.5
        sizeOfNeighborhood=20
        P = self.population(noParticles, dimParticle)
        neighborhoods = self.selectNeighbours(P, sizeOfNeighborhood)
        
        for i in range(noIteratii):
            P = self.iteration(P,neighborhoods,c1,c2,w/(i+1))
        best = 0
        for i in range(1, len(P)):
            if(P[i].fitness < P[best].fitness):
                best = i
        
        fitnessOptim=P[best].fitness
        indOptim=P[best].position
        print(fitnessOptim)
        for i in indOptim:
            print(i)
        return fitnessOptim

###############################################################################################################



class Program:
    def __init__(self):
        self.__ea=EA()
        self.__hc=HillClimb()
        self.__pso=PSO()
    def main(self):
        
        while True:
            i=int(input('0.Exit\n1.EA\n2.Hill Climb\n3.PSO\n4.Test EA\n5.Test PSO\n'))
            if i == 1:
                noIt = int(input('Number of iterations: '))
                dimI = int(input('Dimension of an individual: '))
                dimP = int(input('Dimension of the population: '))
                prob = float(input('Probability of mutation: '))
                t = threading.Thread(target=self.__ea.eaMain,args=(noIt,dimP,dimI,prob,))
                t.start()
            elif i == 2:
                dimI = int(input('Dimension of an individual: '))
                t=threading.Thread(target=self.__hc.hcMain,args=(dimI,))
                t.start()
            elif i == 3:
                noIt = int(input('Number of iterations: '))
                dimI = int(input('Dimension of a particle: '))
                dimP = int(input('Dimension of the population: '))
                t = threading.Thread(target=self.__pso.psoMain,args=(dimP,dimI,noIt,))
                t.start()
            elif i == 4:
                testEA()
            elif i == 5:
                testPSO()
            else:
                return
            

def testPSO():
    pso=PSO()
    noIt=1000
    dimI=2
    dimP=40
    results=[]
    for i in range(30):
        f=pso.psoMain(dimP,dimI,noIt)
        results.append(f)
    s=0
    for i in results:
        s+=i
    mean=s/len(results)
    std=0
    for i in results:
        std+=((i-mean)*(i-mean))
    std/=len(results)
    std=sqrt(std)
    
    print("The mean is: ",mean)
    print("The standard deviation is: ",std)
    
    plt.plot(results,'ro')
    plt.ylabel("Fitness")
    plt.show()
def testEA():
    noIt=1000
    dimI=2
    dimP=40
    prob=0.2
    results=[]
    ea=EA()
    for i in range(30):
        f=ea.eaMain(noIt,dimP,dimI,prob)
        results.append(f)
    s=0
    for i in results:
        s+=i
    mean=s/len(results)
    std=0
    for i in results:
        std+=((i-mean)*(i-mean))
    std/=len(results)
    std=sqrt(std)
    
    print("The mean is: ",mean)
    print("The standard deviation is: ",std)
    
    plt.plot(results,'ro')
    plt.ylabel("Fitness")
    plt.show()
program = Program()
program.main()
    
    