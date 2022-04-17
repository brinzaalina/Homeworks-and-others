import time
from random import randint
import pygame
from pygame import KEYDOWN
from constants import *


class GUI:
    def __init__(self, service):
        self.__service = service
        self.__initial_x = service.drone.x
        self.__initial_y = service.drone.y
        self.__final_x = randint(0, NUMBER_ROWS - 1)
        self.__final_y = randint(0, NUMBER_COLUMNS - 1)

    def map_image(self, colour=BLUE, background=WHITE):
        environment = self.__service.map
        imagine = pygame.Surface((COLUMN_SIZE * environment.m, ROW_SIZE * environment.n))
        brick = pygame.Surface((COLUMN_SIZE, ROW_SIZE))
        brick.fill(colour)
        imagine.fill(background)
        for i in range(environment.n):
            for j in range(environment.m):
                if environment.surface[i][j] == 1:
                    imagine.blit(brick, (j * COLUMN_SIZE, i * ROW_SIZE))
        return imagine

    def map_with_drone(self, mapImage):
        drona = pygame.image.load("drona.png")
        mapImage.blit(drona, (self.__service.drone.y * COLUMN_SIZE, self.__service.drone.x * ROW_SIZE))
        return mapImage

    @staticmethod
    def display_with_path(image, path, color):
        mark = pygame.Surface((NUMBER_COLUMNS, NUMBER_ROWS))
        mark.fill(color)
        for move in path:
            image.blit(mark, (move[1] * COLUMN_SIZE, move[0] * ROW_SIZE))
        return image

    def start(self):
        pygame.init()
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")
        screen = pygame.display.set_mode((1200, 400))
        screen.fill(WHITE)

        while self.__service.map.surface[self.__final_x][self.__final_y] == 1:
            self.__final_x = randint(0, NUMBER_ROWS - 1)
            self.__final_y = randint(0, NUMBER_COLUMNS - 1)

        print("Path starts at: ({}, {}) and ends at: ({}, {})".format(self.__initial_x, self.__initial_y, self.__final_x, self.__final_y))

        running = True
        greedy_done = False
        a_star_done = False
        simulated_annealing_done = False

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            # GREEDY
            greedy_start_time = time.time()
            greedy_path = self.__service.search_greedy(self.__initial_x, self.__initial_y, self.__final_x, self.__final_y)
            greedy_end_time = time.time()
            greedy_total_time = greedy_end_time - greedy_start_time
            if len(greedy_path) == 0:
                print("The path does not exist.")
                return
            if not greedy_done:
                print("The path found with Greedy: {}".format(greedy_path))
                print("Execution time for Greedy: {}".format(str(greedy_total_time)))
                greedy_done = True
            screen.blit(self.display_with_path(self.map_image(), greedy_path, GREEN), (0, 0))

            # A*
            a_star_start_time = time.time()
            a_star_path = self.__service.search_a_star(self.__initial_x, self.__initial_y, self.__final_x, self.__final_y)
            a_star_end_time = time.time()
            a_star_total_time = a_star_end_time - a_star_start_time
            if len(a_star_path) == 0:
                print("The path does not exist.")
                return
            if not a_star_done:
                print("The path found with A*: {}".format(a_star_path))
                print("Execution time for A*: {}".format(str(a_star_total_time)))
                a_star_done = True
            screen.blit(self.display_with_path(self.map_image(GRAYBLUE), a_star_path, RED), (400, 0))
            pygame.display.flip()

            # SIMULATED ANNEALING
            if not simulated_annealing_done:
                simulated_annealing_start_time = time.time()
                simulated_annealing_path = self.__service.search_simulated_annealing(self.__initial_x, self.__initial_y, self.__final_x, self.__final_y, 50)
                simulated_annealing_end_time = time.time()
                simulated_annealing_total_time = simulated_annealing_end_time - simulated_annealing_start_time
                print("The path found with Simulated Annealing: {}".format(simulated_annealing_path))
                print("Execution time for Simulated Annealing: {}".format(str(simulated_annealing_total_time)))
                simulated_annealing_done = True
                screen.blit(self.display_with_path(self.map_image(PALEBLUE), simulated_annealing_path, PALEORANGE),(800, 0))
                pygame.display.flip()

        pygame.quit()
