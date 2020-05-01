# -*- coding: utf-8 -*-
"""
Created on Fri Apr  3 11:08:06 2020

@author: Andreas-PC
"""

import random
import itertools
import math
import copy

class ant:
    def __init__(self,size):
        self.size = size
        self.path = [random.randint(0, size-1)]


    def buildSol(path, perms):
        """
        Maps every index from path to its permutation
        """
        return [perms[perm_index] for perm_index in path]

    def nextMove(self,perms):
        new = []
        for iperm in range(len(perms)):
            if iperm not in self.path:
                path_copy = copy.deepcopy(self.path)
                path_copy.append(iperm)
                if self.fitness(path_copy, perms) == 0:
                    new.append(iperm)
        return copy.deepcopy(new)
    
    def distMove(self, move, perms):
        dummy = ant(self.size)
        dummy.path = copy.deepcopy(self.path)
        dummy.path.append(move)
        return len(perms) - len(dummy.nextMove(perms))
    
    def addMove(self, trace, perms, alpha, beta, q0):
        # Add move if possible
        poss = [0 for _ in range(len(perms))]
        next_moves = self.nextMove(perms)

        if len(next_moves) == 0:
            return

        # Set the dist
        for move in next_moves:
            poss[move] = self.distMove(move, perms)

        # Compute the product trace^alpha and visibility^beta
        poss = [(trace[self.path[-1]][i] ** alpha) * (poss[i] ** beta) for i in range(len(poss))]

        if random.random() < q0:
            poss = [[i, poss[i]] for i in range(len(poss))]
            poss = max(poss, key=lambda pair: pair[1])
            self.path.append(poss[0])
        else:
            s = sum(poss)
            if s == 0:
                return
            self.path.append(copy.deepcopy(random.choice(next_moves)))
        return True

        
        
    def fitness(self,path, perms):
        #computes the fitness only on colums 
        sol = ant.buildSol(path, perms)
        if len(sol) == 0:
            return 1000000
        fit = 0
        for col in range(len(sol[0])):
            sett = set()
            for line in sol:
                sett.add(line[col])
            fit += len(path) - len(sett)

        return fit

class Controller:
    def __init__(self, problem):
        self.p = problem
        self.population = self.geneneratePopulation()

        # Shared list of  all possible permutations
        self.all_perms = list(itertools.permutations([x for x in range(1, self.p.sol_size+1)]))
        random.shuffle(self.all_perms)

        fact = math.factorial(self.p.sol_size)
        self.trace = [[1 for _ in range(fact)] for _ in range(fact)]

    def geneneratePopulation(self):
        return [ant(self.p.sol_size) for _ in range(self.p.nr_ants)]

    def epoch(self):
        ants = self.geneneratePopulation()
        for step in range(self.p.sol_size):
            for ant in ants:
                ant.addMove(self.trace, self.all_perms, self.p.alpha, self.p.beta, self.p.q0)

        d_trace = [1.0 / (ant.fitness(ant.path, self.all_perms)+1) for ant in ants]
        for i in range(self.p.sol_size):
            for j in range(self.p.sol_size):
                self.trace[i][j] = (1 - self.p.rho) * self.trace[i][j]

        for i in range(len(ants)):
            for j in range(len(ants[i].path) - 1):
                x = ants[i].path[j]
                y = ants[i].path[j+1]
                self.trace[x][y] += d_trace[i]

        fit = [[ant.fitness(ants[i].path, self.all_perms), i] for i in range(len(ants))]
        fit = min(fit)
        return ants[fit[1]]

    def combineSolutions(self, first_ant, second_ant, permutations):
        final_sol = []
        aux1 = ant.buildSol(first_ant.path, permutations)
        aux2 = ant.buildSol(second_ant.path, permutations)
        final_sol.extend(aux1)
        final_sol.extend(aux2)
        return final_sol

    def fitness(self, solution):
        sett = set()
        size = len(solution)
        for i in range(size // 2):
            for j in range(len(solution[i])):
                sett.add((solution[i][j], solution[i + size // 2][j]))
        return self.p.sol_size ** 2 - len(sett)

    def ACO(self):
        first_half_sols = []
        second_half_sols = []

        for epoch in range(self.p.nr_ephocs):
            first_half_sols.append(self.epoch())
            second_half_sols.append(self.epoch())

        best_sol = []
        best_fit = 1000000
        for index in range(len(first_half_sols)):
            first_half = first_half_sols[index]
            second_half = second_half_sols[index]

            sol = self.combineSolutions(first_half, second_half, self.all_perms)
            fit = self.fitness(sol)

            if fit == 0:
                return sol
            elif fit < best_fit:
                best_fit = fit
                best_sol = sol

        return best_sol
    
class Problem:
    def __init__(self, nr_epochs, sol_size, nr_ants, alpha, beta, rho, q0):
        self.nr_ephocs = nr_epochs
        self.sol_size = sol_size
        self.nr_ants = nr_ants
        self.alpha = alpha
        self.beta = beta
        self.rho = rho
        self.q0 = q0
        
def prettyPrint(solution):
    s = 'Solution:\n'
    size = len(solution)
    for i in range(size // 2):
        for j in range(len(solution[i])):
            s += str((solution[i][j], solution[i+size//2][j])) + ' '
        s += '\n'
    print(s)
    
def main():
    problem = Problem(100, 3, 50, 1.9, 0.9, 0.05, 0.5)
    controller = Controller(problem)
    print('Hold on, it will take a while!')
    solution = controller.ACO()
    prettyPrint(solution)

main()