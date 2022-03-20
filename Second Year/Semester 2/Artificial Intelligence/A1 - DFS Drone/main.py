from random import randint
from constants import *
from domain.domain import Environment, DMap, Drone
from gui.gui import GUI
from service.service import Service


def main():
    # we create the environment
    e = Environment()
    e.load_environment("test2.map")
    # we create the map
    m = DMap()
    # we position the drone somewhere in the area
    x = randint(0, NUMBER_ROWS)
    y = randint(0, NUMBER_COLUMNS)
    # create the drone
    d = Drone(x, y)
    service = Service(e, d, m)
    move = AUTOMATIC
    gui = GUI(service, move)
    gui.start()


if __name__ == "__main__":
    main()
