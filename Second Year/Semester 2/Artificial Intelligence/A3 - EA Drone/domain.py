# -*- coding: utf-8 -*-
import copy
import pickle
from random import *
import numpy as np
from utils import *


class Drone:
    def __init__(self, x, y, battery=20):
        self.__x = x
        self.__y = y
        self.__battery = battery

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    @property
    def battery(self):
        return self.__battery


class Individual:
    def __init__(self, drone, drone_map):
        self.__size = drone.battery
        self.__x = [randint(0, 3) for _ in range(drone.battery)]
        self.__f = None
        self.__drone = drone
        self.__drone_map = drone_map
        self.__visited = []

    @property
    def get_fitness(self):
        self.fitness()
        return self.__f

    @property
    def get_chromosome(self):
        return self.__x

    @property
    def get_drone(self):
        return self.__drone

    @property
    def get_map(self):
        return self.__drone_map

    def read_sensors(self, x, y):
        readings = [0, 0, 0, 0]
        # UP
        xf = x - 1
        while (xf >= 0) and (self.get_map.surface[xf][y] == 0):
            if (xf, y) not in self.__visited:
                readings[UP] = readings[UP] + 1
                self.__visited.append((xf, y))
            xf = xf - 1

        # DOWN
        xf = x + 1
        while (xf < self.get_map.n) and (self.get_map.surface[xf][y] == 0):
            if (xf, y) not in self.__visited:
                readings[DOWN] = readings[DOWN] + 1
                self.__visited.append((xf, y))
            xf = xf + 1

        # LEFT
        yf = y + 1
        while (yf < self.get_map.m) and (self.get_map.surface[x][yf] == 0):
            if (x, yf) not in self.__visited:
                readings[LEFT] = readings[LEFT] + 1
                self.__visited.append((x, yf))
            yf = yf + 1

        # RIGHT
        yf = y - 1
        while (yf >= 0) and (self.get_map.surface[x][yf] == 0):
            if (x, yf) not in self.__visited:
                readings[RIGHT] = readings[RIGHT] + 1
                self.__visited.append((x, yf))
            yf = yf - 1

        return sum(readings)

    def fitness(self):
        # compute the fitness for the individual
        # and save it in self.__f
        self.__visited = []
        sum_fitness = self.read_sensors(self.get_drone.x, self.get_drone.y)
        position = (self.get_drone.x, self.get_drone.y)
        moves = 0
        for x in self.get_chromosome:
            moves += 1
            direction = v[x]
            new_x = position[0] + direction[0]
            new_y = position[1] + direction[1]
            if 0 <= new_x < self.get_map.m and 0 <= new_y < self.get_map.n and self.get_map.surface[new_x][new_y] == 0:
                fitness = self.read_sensors(new_x, new_y)
                sum_fitness += fitness
            else:
                sum_fitness -= 20
            position = (new_x, new_y)
            if moves == self.get_drone.battery:
                break

        self.__f = sum_fitness

    def mutate(self, mutateProbability=0.04):
        if random() < mutateProbability:
            # perform a mutation with respect to the representation
            # random resetting mutation
            self.__x[randint(0, self.__size - 1)] = randint(0, 3)

    def crossover(self, otherParent, crossoverProbability=0.8):
        offspring1, offspring2 = Individual(self.get_drone, self.get_map), Individual(self.get_drone, self.get_map)
        if random() < crossoverProbability:
            # perform the crossover between the self and the otherParent
            # N cutting-points crossover - in our case, just one cutting point
            part = randint(0, self.__size)
            offspring1.__x = self.__x[:part] + otherParent.__x[part:]
            offspring2.__x = otherParent.__x[:part] + self.__x[part:]
        return offspring1, offspring2


class Population:
    def __init__(self, drone, drone_map, populationSize=10):
        self.__populationSize = populationSize
        self.__v = [Individual(drone, drone_map) for x in range(populationSize)]
        self.evaluate()

    def evaluate(self):
        # evaluates the population
        for x in self.__v:
            x.fitness()

    def selection(self, k=3):
        # perform a selection of k individuals from the population
        # and returns that selection
        sorted_individuals = copy.deepcopy(self.individuals)
        sorted_individuals.sort(key=lambda x: x.get_fitness, reverse=True)
        return sorted_individuals[:k]

    @property
    def individuals(self):
        return self.__v

    @individuals.setter
    def individuals(self, newIndividuals):
        self.__v = newIndividuals

    def add_individual(self, individual):
        self.individuals.append(individual)


class Map:
    def __init__(self, n=20, m=20):
        self.n = n
        self.m = m
        self.surface = np.zeros((self.n, self.m))

    def random_map(self, fill=0.2):
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string = string + str(int(self.surface[i][j]))
            string = string + "\n"
        return string

    def save_map(self, map_name):
        with open(map_name, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def load_map(self, map_name):
        with open(map_name, "rb") as f:
            dummy = pickle.load(f)
            self.n = dummy.n
            self.m = dummy.m
            self.surface = dummy.surface
            f.close()
