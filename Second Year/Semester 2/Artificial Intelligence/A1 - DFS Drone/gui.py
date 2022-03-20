from time import sleep

import pygame
from pygame import KEYDOWN

from constants import *


class GUI:
    def __init__(self, service, move):
        self.__service = service
        self.__move = move

    def environment_image(self, colour=BLUE, background=WHITE):
        environment = self.__service.environment
        imagine = pygame.Surface((COLUMN_SIZE * environment.columns, ROW_SIZE * environment.rows))
        brick = pygame.Surface((COLUMN_SIZE, ROW_SIZE))
        brick.fill(colour)
        imagine.fill(background)
        for i in range(environment.rows):
            for j in range(environment.columns):
                if environment.surface[i][j] == 1:
                    imagine.blit(brick, (j * COLUMN_SIZE, i * ROW_SIZE))
        return imagine

    def drone_map_image(self, x, y):
        drone_map = self.__service.drone_map
        imagine = pygame.Surface((COLUMN_SIZE * drone_map.columns, ROW_SIZE * drone_map.rows))
        brick = pygame.Surface((COLUMN_SIZE, ROW_SIZE))
        empty = pygame.Surface((COLUMN_SIZE, ROW_SIZE))
        empty.fill(WHITE)
        brick.fill(BLACK)
        imagine.fill(GRAYBLUE)
        for i in range(drone_map.rows):
            for j in range(drone_map.columns):
                if drone_map.surface[i][j] == 1:
                    imagine.blit(brick, (j * COLUMN_SIZE, i * ROW_SIZE))
                elif drone_map.surface[i][j] == 0:
                    imagine.blit(empty, (j * COLUMN_SIZE, i * ROW_SIZE))

        drona = pygame.image.load("drona.png")
        imagine.blit(drona, (y * COLUMN_SIZE, x * ROW_SIZE))
        return imagine

    def start(self):
        pygame.init()
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("drone exploration")

        # create a surface on screen that has the size of 800 x 400
        screen = pygame.display.set_mode((self.__service.environment.columns * COLUMN_SIZE * 2, self.__service.environment.rows * ROW_SIZE))
        screen.fill(WHITE)
        screen.blit(self.environment_image(), (0, 0))

        running = True
        while running:
            if self.__move == MANUAL:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        running = False
                        if event.type == KEYDOWN:
                            # d.move_dsf(m)
                            self.__service.move()
            if self.__move == AUTOMATIC:
                self.__service.move_dfs()
                sleep(0.75)

            if self.__service.drone.x is None:
                running = False
            else:
                self.__service.drone_map.mark_detected_walls(self.__service.environment, self.__service.drone.x, self.__service.drone.y)
                screen.blit(self.drone_map_image(self.__service.drone.x, self.__service.drone.y), (COLUMN_SIZE * self.__service.environment.columns, 0))
                pygame.display.flip()

        pygame.quit()