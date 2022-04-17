import pickle
from random import random
import numpy as np

from constants import *


class Map:
    def __init__(self):
        self.n = NUMBER_ROWS
        self.m = NUMBER_COLUMNS
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

    def save_map(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def load_map(self, numFile):
        with open(numFile, "rb") as f:
            dummy = pickle.load(f)
            self.n = dummy.n
            self.m = dummy.m
            self.surface = dummy.surface
            f.close()


class Drone:
    def __init__(self, x, y):
        self.__x = x
        self.__y = y

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, newX):
        self.__x = newX

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, newY):
        self.__y = newY

