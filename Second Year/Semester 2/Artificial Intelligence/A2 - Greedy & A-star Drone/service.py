import math
import random

import pygame
from pygame import K_UP, K_DOWN, K_LEFT, K_RIGHT

from constants import *


class Service:
    def __init__(self, map, drone):
        self.__map = map
        self.__drone = drone

    @property
    def map(self):
        return self.__map

    @property
    def drone(self):
        return self.__drone

    def move(self):
        pressed_keys = pygame.key.get_pressed()
        if self.drone.x > 0:
            if pressed_keys[K_UP] and self.map.surface[self.drone.x - 1][self.drone.y] == 0:
                self.drone.x = self.drone.x - 1
        if self.drone.x < 19:
            if pressed_keys[K_DOWN] and self.map.surface[self.drone.x + 1][self.drone.y] == 0:
                self.drone.x = self.drone.x + 1
        if self.drone.y > 0:
            if pressed_keys[K_LEFT] and self.map.surface[self.drone.x][self.drone.y - 1] == 0:
                self.drone.y = self.drone.y - 1
        if self.drone.y < 19:
            if pressed_keys[K_RIGHT] and self.map.surface[self.drone.x][self.drone.y + 1] == 0:
                self.drone.y = self.drone.y + 1

    @staticmethod
    def manhattan_distance(node1, node2):
        return abs(node1[0] - node2[0]) + abs(node1[1] - node2[1])

    @staticmethod
    def build_path(prev, final_x, final_y):
        path = [(final_x, final_y)]
        coordinates = prev[(final_x, final_y)]
        while coordinates != (None, None):
            path.append(coordinates)
            coordinates = prev[coordinates]
        path.reverse()
        return path

    def search_a_star(self, initial_x, initial_y, final_x, final_y):
        found = False
        prev = dict()
        prev[(initial_x, initial_y)] = (None, None)
        visited = []
        to_visit = [(initial_x, initial_y)]
        number_steps = dict()
        number_steps[(initial_x, initial_y)] = 0
        while len(to_visit) != 0 and not found:
            node = to_visit.pop(0)
            visited.append(node)
            if node == (final_x, final_y):
                found = True
            else:
                aux = []
                for variation in VARIATIONS:
                    new_x = node[0] + variation[0]
                    new_y = node[1] + variation[1]
                    if -1 < new_x < NUMBER_ROWS and -1 < new_y < NUMBER_COLUMNS and self.map.surface[new_x][new_y] == 0 and (new_x, new_y) not in visited:
                        if (new_x, new_y) not in to_visit:
                            aux.append((new_x, new_y))
                            prev[(new_x, new_y)] = node
                            number_steps[(new_x, new_y)] = number_steps[node] + 1
                        else:
                            if number_steps[(new_x, new_y)] > number_steps[node] + 1:
                                to_visit.remove((new_x, new_y))
                                aux.append((new_x, new_y))
                                prev[(new_x, new_y)] = node
                                number_steps[(new_x, new_y)] = number_steps[node] + 1
                to_visit.extend(aux)
                to_visit.sort(key=lambda coord: self.manhattan_distance(coord, (final_x, final_y)) + number_steps[coord])
        if found:
            return self.build_path(prev, final_x, final_y)
        else:
            return []

    def search_greedy(self, initial_x, initial_y, final_x, final_y):
        found = False
        visited = []
        prev = dict()
        prev[(initial_x, initial_y)] = (None, None)
        to_visit = [(initial_x, initial_y)]
        while len(to_visit) != 0 and not found:
            node = to_visit.pop(0)
            visited.append(node)
            if node == (final_x, final_y):
                found = True
            else:
                aux = []
                for variation in VARIATIONS:
                    new_x = node[0] + variation[0]
                    new_y = node[1] + variation[1]
                    if -1 < new_x < NUMBER_ROWS and -1 < new_y < NUMBER_COLUMNS and self.map.surface[new_x][new_y] == 0 and (new_x, new_y) not in visited:
                        aux.append((new_x, new_y))
                        prev[(new_x, new_y)] = node
                to_visit.extend(aux)
                to_visit.sort(key=lambda coord: self.manhattan_distance(coord, (final_x, final_y)))
        if found:
            return self.build_path(prev, final_x, final_y)
        else:
            return []

    def search_simulated_annealing(self, initial_x, initial_y, final_x, final_y, initial_temp=1000):
        position = (initial_x, initial_y)
        path = [position]
        k = 0
        while position != (final_x, final_y):
            k += 1
            temp = initial_temp / (k + 1)
            neighbours = []
            for variation in VARIATIONS:
                new_position = (position[0] + variation[0], position[1] + variation[1])
                if -1 < new_position[0] < NUMBER_ROWS and -1 < new_position[1] < NUMBER_COLUMNS and self.map.surface[new_position[0]][new_position[1]] == 0:
                    neighbours.append(new_position)
            neighbour = random.choice(neighbours)
            delta = self.manhattan_distance(neighbour, (final_x, final_y)) - self.manhattan_distance(position, (final_x, final_y))
            if delta < 0:
                position = neighbour
                path.append(position)
            else:
                probability = math.exp(-delta/temp)
                r = random.uniform(0, 1)
                if r < probability:
                    position = neighbour
                    path.append(position)
        return path
