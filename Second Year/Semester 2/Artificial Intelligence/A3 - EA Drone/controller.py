import random as rand
from copy import deepcopy

import numpy as np

from repository import *


class Controller:
    def __init__(self):
        self.__repo = Repository()

    def get_map(self):
        return self.__repo.map

    def set_map(self, new_map):
        self.__repo.map = new_map

    def get_drone(self):
        return self.__repo.drone

    def iteration(self, population):
        # args - list of parameters needed to run one iteration
        # a iteration:
        # selection of the parents
        # create offsprings by crossover of the parents
        # apply some mutations
        # selection of the survivors
        individuals = population.individuals
        ind1 = randint(0, len(individuals) - 1)
        ind2 = randint(0, len(individuals) - 1)
        while ind1 == ind2:
            ind2 = randint(0, len(individuals) - 1)

        parent1 = individuals[ind1]
        parent2 = individuals[ind2]

        offspring1, offspring2 = parent1.crossover(parent2)
        offspring1.mutate()
        offspring2.mutate()

        if offspring1.get_fitness > offspring2.get_fitness:
            population.add_individual(offspring1)
        else:
            population.add_individual(offspring2)
        
    def run(self, rand_seed, population_size, nr_iterations):
        # args - list of parameters needed in order to run the algorithm
        
        # until stop condition
        #    perform an iteration
        #    save the information needed for the statistics
        
        # return the results and the info for statistics
        rand.seed(rand_seed)
        population = Population(self.__repo.drone, self.__repo.map, population_size)
        self.__repo.add_population(population)
        best_individual = None
        averages = []
        for iteration in range(nr_iterations):
            self.iteration(population)
            population.individuals = population.selection(population_size)
            population_fitness = []
            for individual in population.individuals:
                population_fitness.append(individual.get_fitness)
                if best_individual is None or best_individual.get_fitness < individual.get_fitness:
                    best_individual = deepcopy(individual)
            averages.append(np.average(population_fitness))

        return best_individual, averages

    def solver(self, population_size, nr_iterations, last_seed=5):
        # args - list of parameters needed in order to run the solver
        
        # create the population,
        # run the algorithm
        # return the results and the statistics
        fitnesses = []
        for i in range(last_seed):
            best, _ = self.run(i, population_size, nr_iterations)
            print(str(i) + "     " + str(best.get_fitness))
            fitnesses.append(best.get_fitness)

        return fitnesses
       