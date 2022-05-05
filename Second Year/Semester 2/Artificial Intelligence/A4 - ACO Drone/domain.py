import random
from queue import Queue

import numpy.random

from const import *


class DMap:
    def __init__(self, n, m, battery):
        self.surface = None
        self.x = None
        self.y = None
        self.battery = battery
        self.n = n
        self.m = m
        self.sensor_index = [[None for _ in range(self.m)] for _ in range(self.n)]
        self.number_of_sensors = 0
        self.list_of_sensors = []
        self.paths_between_sensors = []
        self.starting_index = None

    def update_paths(self):
        self.number_of_sensors = 0
        self.list_of_sensors = []
        self.surface[self.x][self.y] = 1
        for i in range(self.n):
            for j in range(self.m):
                if self.surface[i][j] == 1:
                    self.sensor_index[i][j] = self.number_of_sensors
                    self.list_of_sensors.append((i, j))
                    if i == self.x and j == self.y:
                        self.starting_index = self.number_of_sensors
                    self.number_of_sensors += 1
        self.paths_between_sensors = [[None for _ in range(self.number_of_sensors)] for _ in range(self.number_of_sensors)]
        for sensor in range(self.number_of_sensors):
            q = Queue()
            d = [[None for _ in range(self.m)] for _ in range(self.n)]
            prev = [[None for _ in range(self.m)] for _ in range(self.n)]
            sensor_position = self.list_of_sensors[sensor]
            d[sensor_position[0]][sensor_position[1]] = 0
            q.put(sensor_position)
            while not q.empty():
                current_sensor = q.get()
                for direction in DIRECTIONS:
                    next_pos = (current_sensor[0] + direction[0], current_sensor[1] + direction[1])
                    if 0 <= next_pos[0] < self.n and 0 <= next_pos[1] < self.m and self.surface[next_pos[0]][next_pos[1]] != 2:
                        if d[next_pos[0]][next_pos[1]] is None:
                            d[next_pos[0]][next_pos[1]] = d[current_sensor[0]][current_sensor[1]] + 1
                            q.put(next_pos)
                            prev[next_pos[0]][next_pos[1]] = current_sensor
            for i in range(self.n):
                for j in range(self.m):
                    if self.surface[i][j] == 1 and (i != sensor_position[0] or j != sensor_position[1]) and d[i][j] is not None:
                        current_path = []
                        current_cell = (i, j)
                        while current_cell != sensor_position:
                            current_path.append(current_cell)
                            current_cell = prev[current_cell[0]][current_cell[1]]
                        self.paths_between_sensors[sensor][self.sensor_index[i][j]] = list(reversed(current_path))

    def random_map(self, wall_fill_factor=0.2, sensor_fill_factor=0.03):
        self.surface = [[2 if random.random() < wall_fill_factor else 1 if random.random() < sensor_fill_factor else 0 for _ in range(self.m)] for _ in range(self.n)]
        self.x = random.randrange(self.n)
        self.y = random.randrange(self.m)
        while self.surface[self.x][self.y] != 0:
            self.x = random.randrange(self.n)
            self.y = random.randrange(self.m)
        self.update_paths()


class Ant:
    def __init__(self, drone_map):
        self.drone_map = drone_map
        self.path = [(drone_map.x, drone_map.y, 0)]
        self.sensor_path = [(self.drone_map.starting_index, 0)]
        self.battery_left = drone_map.battery
        self.visited_sensors = [False for _ in range(self.drone_map.number_of_sensors)]
        self.visited_sensors[self.drone_map.starting_index] = True

    def coverage(self):
        marked = [[0 for _ in range(self.drone_map.m)] for _ in range(self.drone_map.n)]
        for cell in self.path:
            if cell[2] != 0:
                for direction in DIRECTIONS:
                    i = cell[0]
                    j = cell[1]
                    for _ in range(cell[2]):
                        new_neighbour = (i + direction[0], j + direction[1])
                        is_wall = True
                        if 0 <= new_neighbour[0] < self.drone_map.n and 0 <= new_neighbour[1] < self.drone_map.m:
                            if self.drone_map.surface[new_neighbour[0]][new_neighbour[1]] != 2:
                                marked[new_neighbour[0]][new_neighbour[1]] = 1
                                i = new_neighbour[0]
                                j = new_neighbour[1]
                                is_wall = False
                        if is_wall:
                            break
        return sum([sum(row) for row in marked])

    def go_to_next_sensor(self, pheromone_matrix, alpha, beta, q0):
        current_sensor = self.sensor_path[-1][0]
        possible_next_cells = []
        for sensor in range(self.drone_map.number_of_sensors):
            if not self.visited_sensors[sensor] and self.drone_map.paths_between_sensors[current_sensor][sensor] is not None:
                for spend_energy in range(1, MAX_SENSOR_COVERAGE + 1):
                    tau = pheromone_matrix[current_sensor][sensor][spend_energy]
                    distance = len(self.drone_map.paths_between_sensors[current_sensor][sensor])
                    if self.battery_left < distance + spend_energy:
                        continue
                    # visibility ^ beta * trace ^ alpha
                    p = (1 / (spend_energy + distance)) ** beta * tau ** alpha
                    next_cell = [(sensor, spend_energy), p]
                    possible_next_cells.append(next_cell)
        if len(possible_next_cells) == 0:
            return
        if random.random() < q0:
            chosen_sensor = max(possible_next_cells, key=lambda x: x[1])[0]
        else:
            prob_sum = sum([move[1] for move in possible_next_cells])
            next_cell = numpy.random.choice([i for i in range(len(possible_next_cells))], p=[move[1]/prob_sum for move in possible_next_cells])
            chosen_sensor = possible_next_cells[next_cell][0]
        self.visited_sensors[chosen_sensor[0]] = True
        path = [(cell[0], cell[1], 0) for cell in self.drone_map.paths_between_sensors[current_sensor][chosen_sensor[0]]]
        self.path.extend(path)
        self.path[-1] = (self.path[-1][0], self.path[-1][1], chosen_sensor[1])
        self.sensor_path.append(chosen_sensor)
        self.battery_left -= self.path[-1][2] + len(path)

