from random import randint
from constants import *
from domain.domain import Map, Drone
from gui.gui import GUI
from service.service import Service


def main():
    m = Map()
    m.load_map("test1.map")

    # we position the drone somewhere in the area
    x = randint(0, NUMBER_ROWS - 1)
    y = randint(0, NUMBER_COLUMNS - 1)

    while m.surface[x][y] == 1:
        x = randint(0, NUMBER_ROWS - 1)
        y = randint(0, NUMBER_COLUMNS - 1)

    # create drone
    d = Drone(x, y)
    service = Service(m, d)
    gui = GUI(service)
    gui.start()


if __name__ == "__main__":
    # call the main function
    main()
