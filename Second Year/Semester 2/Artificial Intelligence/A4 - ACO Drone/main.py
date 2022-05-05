from controller import Controller
from gui import *
from domain import DMap
from const import *


def main():
    drone_map = DMap(ROWS, COLUMNS, BATTERY)
    drone_map.random_map()
    controller = Controller(drone_map)
    solution = None
    for _ in range(ITERATIONS):
        current_solution = controller.iterate()
        if solution is None or solution.coverage() < current_solution.coverage():
            solution = current_solution
    print("The solution will see {} cells".format(solution.coverage()))
    print("The order of visiting the sensors is: {}".format(solution.sensor_path))
    moving_drone(controller.drone_map, solution.path, BATTERY)


if __name__ == "__main__":
    main()
