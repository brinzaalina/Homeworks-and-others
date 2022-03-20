from termcolor import colored


class Circle:
    def __init__(self, color):
        """
        Initializer for the Circle class
        :param color: the color of the circle
        """
        self.color = color

    @property
    def get_color(self):
        return self.color

    def __str__(self):
        """
        Function for printing a circle of the specified color
        :return: The colored circle
        """
        return colored('●', str(self.color))


class Board:
    def __init__(self):
        """
        Initializer for the Board class
        It contains a pseudo-matrix which memories the state of the board
        """
        self.matrix = [['●' for x in range(7)] for y in range(6)]

    def __str__(self):
        """
        :return: the configuration of the board as a string/board
        """
        string = ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n'
        string += ' - - - - - - - - - - - - - - -\n'
        for index1 in range(6):
            for index2 in range(7):
                string += ' | '
                string += str(self.matrix[index1][index2])
            string += ' | \n'
            string += ' - - - - - - - - - - - - - - -\n'
        return string


class Player:
    def __init__(self, name, circle):
        """
        Initializer for the Player Class
        :param name: the name of the player
        :param circle: the circle which the player will use
        """
        self.name = name
        self.circle = circle

    @property
    def get_circle(self):
        """
        Getter for the circle attribute
        """
        return self.circle

    @property
    def get_name(self):
        """
        Getter for the name attribute
        """
        return self.name

    def __str__(self):
        return "{} is playing with circles of this color: {}".format(self.name, str(self.circle))


class AI:
    def __init__(self, circle, opponent_circle, difficulty):
        """
        Initializer for the AI class
        :param circle: the circle to be used by the computer
        :param opponent_circle: the circle used by the opponent
        :param difficulty: the depth at which the computer will look further for its moves
        """
        self.circle = circle
        self.opponent_circle = opponent_circle
        self.difficulty = difficulty

    @property
    def get_circle(self):
        """
        Getter for the circle attribute
        """
        return self.circle

    def __str__(self):
        return "The computer is playing with circles of this color: {}".format(str(self.circle))
