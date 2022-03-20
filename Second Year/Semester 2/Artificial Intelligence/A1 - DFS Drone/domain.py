import pickle
from random import random
from constants import *
import numpy as np


class Environment:
    def __init__(self):
        self.__n = NUMBER_ROWS
        self.__m = NUMBER_COLUMNS
        self.__surface = np.zeros((self.__n, self.__m))

    @property
    def rows(self):
        return self.__n

    @rows.setter
    def rows(self, newRows):
        self.__n = newRows

    @property
    def columns(self):
        return self.__m

    @columns.setter
    def columns(self, newColumns):
        self.__m = newColumns

    @property
    def surface(self):
        return self.__surface

    @surface.setter
    def surface(self, newSurface):
        self.__surface = newSurface

    def random_map(self, fill=0.2):
        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.__n):
            for j in range(self.__m):
                string = string + str(int(self.__surface[i][j]))
            string = string + "\n"
        return string

    def read_udm_sensors(self, x, y):
        readings = [0, 0, 0, 0]
        # UP
        xf = x - 1
        while (xf >= 0) and (self.__surface[xf][y] == 0):
            xf = xf - 1
            readings[UP] = readings[UP] + 1
        # DOWN
        xf = x + 1
        while (xf < self.__n) and (self.__surface[xf][y] == 0):
            xf = xf + 1
            readings[DOWN] = readings[DOWN] + 1
        # LEFT
        yf = y + 1
        while (yf < self.__m) and (self.__surface[x][yf] == 0):
            yf = yf + 1
            readings[LEFT] = readings[LEFT] + 1
        # RIGHT
        yf = y - 1
        while (yf >= 0) and (self.__surface[x][yf] == 0):
            yf = yf - 1
            readings[RIGHT] = readings[RIGHT] + 1

        return readings

    def save_environment(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def load_environment(self, numFile):
        with open(numFile, "rb") as f:
            dummy = pickle.load(f)
            self.rows = dummy.rows
            self.columns = dummy.columns
            self.surface = dummy.surface
            f.close()


class DMap:
    def __init__(self):
        self.__rows = NUMBER_ROWS
        self.__columns = NUMBER_COLUMNS
        self.__surface = np.zeros((self.__rows, self.__columns))
        for i in range(self.__rows):
            for j in range(self.__columns):
                self.surface[i][j] = -1

    @property
    def rows(self):
        return self.__rows

    @property
    def columns(self):
        return self.__columns

    @property
    def surface(self):
        return self.__surface

    def mark_detected_walls(self, e, x, y):
        walls = e.read_udm_sensors(x, y)
        i = x - 1
        if walls[UP] > 0:
            while (i >= 0) and (i >= x - walls[UP]):
                self.surface[i][y] = 0
                i = i - 1
        if i >= 0:
            self.surface[i][y] = 1

        i = x + 1
        if walls[DOWN] > 0:
            while (i < self.__rows) and (i <= x + walls[DOWN]):
                self.surface[i][y] = 0
                i = i + 1
        if i < self.__rows:
            self.surface[i][y] = 1

        j = y + 1
        if walls[LEFT] > 0:
            while (j < self.__columns) and (j <= y + walls[LEFT]):
                self.surface[x][j] = 0
                j = j + 1
        if j < self.__columns:
            self.surface[x][j] = 1

        j = y - 1
        if walls[RIGHT] > 0:
            while (j >= 0) and (j >= y - walls[RIGHT]):
                self.surface[x][j] = 0
                j = j - 1
        if j >= 0:
            self.surface[x][j] = 1

        return None


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
