import pygame

from constants import VARIATIONS, NUMBER_ROWS, NUMBER_COLUMNS


class Service:
    def __init__(self, environment, drone, drone_map):
        self.__environment = environment
        self.__drone = drone
        self.__drone_map = drone_map
        self.__visited = []
        self.__stack = []

    @property
    def environment(self):
        return self.__environment

    @property
    def drone(self):
        return self.__drone

    @property
    def drone_map(self):
        return self.__drone_map

    @property
    def visited(self):
        return self.__visited

    @property
    def stack(self):
        return self.__stack

    def move(self):
        pressed_keys = pygame.key.get_pressed()
        if self.drone.x > 0:
            if pressed_keys[pygame.K_UP] and self.drone_map.surface[self.drone.x - 1][self.drone.y] == 0:
                self.drone.x = self.drone.x - 1
        if self.drone.x < 19:
            if pressed_keys[pygame.K_DOWN] and self.drone_map.surface[self.drone.x + 1][self.drone.y] == 0:
                self.drone.x = self.drone.x + 1
        if self.drone.y > 0:
            if pressed_keys[pygame.K_LEFT] and self.drone_map.surface[self.drone.x][self.drone.y - 1] == 0:
                self.drone.y = self.drone.y - 1
        if self.drone.y < 19:
            if pressed_keys[pygame.K_RIGHT] and self.drone_map.surface[self.drone.x][self.drone.y + 1] == 0:
                self.drone.y = self.drone.y + 1

    def move_dfs(self):
        self.visited.append((self.drone.x, self.drone.y))
        # order: UP, RIGHT, DOWN, LEFT
        for variation in VARIATIONS:
            if -1 < self.drone.x + variation[0] < NUMBER_ROWS and -1 < self.drone.y + variation[1] < NUMBER_COLUMNS:
                if self.environment.surface[self.drone.x + variation[0]][self.drone.y + variation[1]] == 0 and (self.drone.x + variation[0], self.drone.y + variation[1]) not in self.visited:
                    self.stack.append((self.drone.x, self.drone.y))
                    self.stack.append((self.drone.x + variation[0], self.drone.y + variation[1]))

        if len(self.stack) != 0:
            current_position = self.stack.pop()
            self.drone.x = current_position[0]
            self.drone.y = current_position[1]
        else:
            self.drone.x = None
            self.drone.y = None

