# imports
import numpy as np

from gui import *
from controller import *
from repository import *
from domain import *
import matplotlib.pyplot as plot

# TODO ui
# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.moving_drone(currentMap, path, speed, markseen)
#              ATENTION! the function doesn't check if the path passes trough walls


class UI:
    def __init__(self):
        self.__controller = Controller()
        self.__best_individual = None
        self.__population_size = 50
        self.__nr_iterations = 100

    def set_parameters(self):
        self.__population_size = input("Population size: ")
        self.__nr_iterations = input("Number of iterations: ")

    @staticmethod
    def plot_graph(averages):
        plot.plot(averages)
        plot.ylim([np.min(averages), None])
        plot.savefig("graph.png")
        plot.close()

    def log_to_file(self, fitnesses, last_seed=30, population_size=50, number_iterations=50):
        log_file = open("results.txt", "a")
        log_file.write("Seeds = [{}, {}]\n".format(1, last_seed))
        log_file.write("Population size = {}, battery = {}\n".format(population_size, 20))
        log_file.write("Iterations = {}, mutation probability = {}, crossover probability = {}\n".format(number_iterations, 0.04, 0.8))
        log_file.write("Average: {}\n".format(np.average(fitnesses)))
        log_file.write("Standard deviation: {}\n".format(np.std(fitnesses)))

    def single_run(self):
        start = time.time()
        best, averages = self.__controller.run(randint(0, 30), self.__population_size, self.__nr_iterations)
        end = time.time()
        total = end - start
        print("The algorithm finished a run in {} seconds.".format(total))
        self.__best_individual = best
        self.plot_graph(averages)

    def run_solver(self):
        fitnesses = self.__controller.solver(self.__population_size, self.__nr_iterations, 30)
        self.log_to_file(fitnesses)

    def view_drone_path(self):
        moving_drone(self.__controller, self.__best_individual)

    @staticmethod
    def main_menu():
        print("0. Exit")
        print("1. Map options")
        print("2. EA options")

    @staticmethod
    def map_options_menu():
        print("0. Exit.")
        print("1. Create a random map.")
        print("2. Load a map.")
        print("3. Save a map.")
        print("4. Visualise map.")

    @staticmethod
    def ea_options_menu():
        print("0. Exit.")
        print("1. Parameters setup.")
        print("2. Single run.")
        print("3. Run the solver.")
        print("4. View the drone moving on a path.")

    def run_map_menu(self):
        new_map = Map()
        done = False
        while not done:
            self.map_options_menu()
            option = input("Choose an option: ")
            if option == "0":
                done = True
            elif option == "1":
                new_map.random_map()
                print("Map successfully generated!")
            elif option == "2":
                map_name = input("Enter the filename for the map: ")
                new_map.load_map(map_name)
                print("Map loaded!")
            elif option == "3":
                map_name = input("Enter the filename for the map: ")
                new_map.save_map(map_name)
                print("Map saved!")
            elif option == "4":
                print(new_map)
            else:
                print("Invalid input.")
        self.__controller.set_map(new_map)

    def run_ea_menu(self):
        done = False
        while not done:
            self.ea_options_menu()
            option = input("Choose an option: ")
            if option == "0":
                done = True
            elif option == "1":
                self.set_parameters()
            elif option == "2":
                self.single_run()
            elif option == "3":
                self.run_solver()
            elif option == "4":
                self.view_drone_path()
            else:
                print("Invalid input.")

    def run(self):
        done = False
        while not done:
            self.main_menu()
            option = input("Choose an option: ")
            if option == "0":
                done = True
            elif option == "1":
                self.run_map_menu()
            elif option == "2":
                self.run_ea_menu()
            else:
                print("Invalid input.")
