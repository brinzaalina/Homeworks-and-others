# -*- coding: utf-8 -*-

import pickle
from domain import *


class Repository:
    def __init__(self):
        self.__populations = []
        self.__dmap = Map()
        self.__drone = Drone(randint(0, 19), randint(0, 19))
        
    def create_population(self, args):
        # args = [populationSize, individualSize] -- you can add more args    
        self.__populations.append(Population(self.__drone, self.__dmap))
        
    @property
    def populations(self):
        return self.__populations

    @property
    def map(self):
        return self.__dmap

    @map.setter
    def map(self, new_map):
        self.__dmap = new_map

    @property
    def drone(self):
        return self.__drone

    def add_population(self, population):
        self.__populations.append(population)

    def load_random_map(self):
        self.__dmap.random_map()
            