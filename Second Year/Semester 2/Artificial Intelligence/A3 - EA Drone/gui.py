# -*- coding: utf-8 -*-

from pygame.locals import *
import pygame, time
from utils import *
from domain import *


def init_py_game(dimension):
    # init the pygame
    pygame.init()
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration with AE")

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode(dimension)
    screen.fill(WHITE)
    return screen


def close_py_game():
    # closes the pygame
    running = True
    # loop for events
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False
    pygame.quit()


def moving_drone(controller, best_individual, speed=500):
    screen = init_py_game((controller.get_map().n * 20, controller.get_map().m * 20))
    # animation of a drone on a path
    brick = pygame.Surface((20, 20))
    path_tile = pygame.Surface((20, 20))
    brick.fill(BLUE)
    path_tile.fill(GREEN)

    map_surface = controller.get_map()
    img = image(map_surface)

    drona = pygame.image.load("drona.png")
    current_position = (controller.get_drone().x, controller.get_drone().y)
    img.blit(drona, (current_position[1] * 20, current_position[0] * 20))
    path = best_individual.get_chromosome
    for i in range(len(path)):
        img.blit(path_tile, (current_position[1] * 20, current_position[0] * 20))
        img_copy = img.copy()
        img_copy.blit(drona, (current_position[1] * 20, current_position[0] * 20))
        img_copy2 = img_copy.copy()
        for index in v:
            x = current_position[0]
            y = current_position[1]
            while 0 <= x + index[0] < map_surface.m and 0 <= y + index[1] < map_surface.n and map_surface.surface[x + index[0]][y + index[1]] != 1:
                x = x + index[0]
                y = y + index[1]
                img_copy2.blit(path_tile, (y * 20, x * 20))
        screen.blit(img_copy2, (0, 0))
        pygame.display.update()
        pygame.time.wait(speed)
        direction_indexes = v[path[i]]
        current_position = (current_position[0] + direction_indexes[0], current_position[1] + direction_indexes[1])
    close_py_game()


def image(currentMap, colour=BLUE, background=WHITE):
    # creates the image of a map

    imagine = pygame.Surface((currentMap.n * 20, currentMap.m * 20))
    brick = pygame.Surface((20, 20))
    brick.fill(colour)
    imagine.fill(background)
    for i in range(currentMap.n):
        for j in range(currentMap.m):
            if currentMap.surface[i][j] == 1:
                imagine.blit(brick, (j * 20, i * 20))

    return imagine
