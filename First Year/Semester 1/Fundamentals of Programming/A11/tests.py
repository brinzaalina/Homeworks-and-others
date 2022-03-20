import unittest

from termcolor import colored

from domain import Circle, Board, Player, AI
from service import BoardService, AIService


class Tests(unittest.TestCase):
    def test_circle(self):
        circle1 = Circle("yellow")
        circle2 = Circle("magenta")
        self.assertEqual(circle1.color, "yellow")
        self.assertEqual(circle2.color, "magenta")
        self.assertEqual(str(circle1), colored('●', "yellow"))
        self.assertEqual(str(circle2), colored('●', "magenta"))

    def test_board(self):
        circle1 = Circle("yellow")
        circle2 = Circle("magenta")
        board = Board()
        board_service = BoardService()
        self.assertEqual(board.matrix[0][1], '●')
        self.assertEqual(str(board), ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n'
                                     ' | ● | ● | ● | ● | ● | ● | ● | \n'
                                     ' - - - - - - - - - - - - - - -\n')
        board_service.move(board, circle1, 1)
        board_service.move(board, circle2, 2)
        self.assertEqual(board_service.is_game_won(board), False)
        board_service.move(board, circle1, 1)
        board_service.move(board, circle2, 3)
        self.assertEqual(board_service.is_game_won(board), False)
        board_service.move(board, circle1, 1)
        board_service.move(board, circle2, 4)
        self.assertEqual(board_service.is_game_won(board), False)
        board_service.move(board, circle1, 1)
        self.assertEqual(board_service.is_game_won(board), True)

        board2 = Board()
        board_service.move(board2, circle1, 1)
        board_service.move(board2, circle2, 1)
        board_service.move(board2, circle1, 2)
        board_service.move(board2, circle2, 2)
        board_service.move(board2, circle1, 3)
        board_service.move(board2, circle2, 1)
        board_service.move(board2, circle1, 4)
        self.assertEqual(board_service.is_game_won(board2), True)

        board3 = Board()
        board_service.move(board3, circle1, 1)
        board_service.move(board3, circle2, 2)
        board_service.move(board3, circle1, 2)
        board_service.move(board3, circle2, 3)
        board_service.move(board3, circle2, 3)
        board_service.move(board3, circle1, 3)
        board_service.move(board3, circle2, 4)
        board_service.move(board3, circle2, 4)
        board_service.move(board3, circle2, 4)
        board_service.move(board3, circle1, 4)
        self.assertEqual(board_service.is_game_won(board3), True)

        board4 = Board()
        board_service.move(board4, circle2, 1)
        board_service.move(board4, circle2, 1)
        board_service.move(board4, circle2, 1)
        board_service.move(board4, circle1, 1)
        board_service.move(board4, circle2, 2)
        board_service.move(board4, circle2, 2)
        board_service.move(board4, circle1, 2)
        board_service.move(board4, circle2, 3)
        board_service.move(board4, circle1, 3)
        board_service.move(board4, circle1, 4)
        self.assertEqual(board_service.is_game_won(board4), True)

        board5 = Board()
        board_service.move(board5, circle1, 0)
        self.assertEqual(board_service.is_draw(board5), False)
        board_service.move(board5, circle2, 0)
        board_service.move(board5, circle1, 0)
        board_service.move(board5, circle1, 0)
        board_service.move(board5, circle2, 0)
        board_service.move(board5, circle1, 0)

        board_service.move(board5, circle2, 1)
        board_service.move(board5, circle1, 1)
        board_service.move(board5, circle2, 1)
        board_service.move(board5, circle2, 1)
        board_service.move(board5, circle1, 1)
        board_service.move(board5, circle1, 1)

        board_service.move(board5, circle1, 2)
        board_service.move(board5, circle2, 2)
        board_service.move(board5, circle1, 2)
        board_service.move(board5, circle1, 2)
        board_service.move(board5, circle2, 2)
        board_service.move(board5, circle2, 2)

        board_service.move(board5, circle2, 3)
        board_service.move(board5, circle1, 3)
        board_service.move(board5, circle2, 3)
        board_service.move(board5, circle2, 3)
        board_service.move(board5, circle1, 3)
        board_service.move(board5, circle2, 3)

        board_service.move(board5, circle1, 4)
        board_service.move(board5, circle2, 4)
        board_service.move(board5, circle1, 4)
        board_service.move(board5, circle1, 4)
        board_service.move(board5, circle2, 4)
        board_service.move(board5, circle1, 4)

        board_service.move(board5, circle2, 5)
        board_service.move(board5, circle1, 5)
        board_service.move(board5, circle2, 5)
        board_service.move(board5, circle2, 5)
        board_service.move(board5, circle1, 5)
        board_service.move(board5, circle1, 5)

        board_service.move(board5, circle1, 6)
        board_service.move(board5, circle2, 6)
        board_service.move(board5, circle1, 6)
        board_service.move(board5, circle1, 6)
        board_service.move(board5, circle2, 6)
        board_service.move(board5, circle2, 6)

        self.assertEqual(board_service.is_draw(board5), True)

        self.assertEqual(board_service.move(board5, circle1, 6), False)

    def test_player(self):
        player1 = Player("Alina", colored('●', 'yellow'))
        player2 = Player("Elena", colored('●', 'magenta'))
        self.assertEqual(player1.get_name, 'Alina')
        self.assertEqual(player2.get_circle, colored('●', 'magenta'))
        self.assertEqual(str(player1), "Alina is playing with circles of this color: {}".format(colored('●', 'yellow')))

    def test_AI(self):
        circle1 = Circle('yellow')
        circle2 = Circle('magenta')
        player1 = Player("Alina", circle1)
        player2 = AI(circle2, player1.get_circle, 2)
        self.assertEqual(str(player2), "The computer is playing with circles of this color: {}".format(str(circle2)))
        board = Board()
        board_service = BoardService()
        ai_service = AIService()
        board_service.move(board, circle1, 0)
        board_service.move(board, circle2, 1)
        board_service.move(board, circle1, 1)
        board_service.move(board, circle2, 2)
        board_service.move(board, circle2, 2)
        board_service.move(board, circle1, 2)
        board_service.move(board, circle2, 2)
        board_service.move(board, circle1, 2)
        board_service.move(board, circle2, 2)
        self.assertEqual(player2.get_circle, circle2)
        self.assertEqual(ai_service.is_legal_move(board, 3), True)
        self.assertEqual(ai_service.is_legal_move(board, 2), False)
        board2 = ai_service.simulate_move(board, 1, player2.get_circle)
        self.assertEqual(board2.matrix[0][2], circle2)
        self.assertEqual(ai_service.find_vertical_connection(4, 2, board, 2, circle2), 1)
        self.assertEqual(ai_service.find_vertical_connection(4, 2, board, 3, circle2), 0)
        self.assertEqual(ai_service.find_vertical_connection(5, 2, board, 2, circle2), 0)
        self.assertEqual(ai_service.find_horizontal_connection(5, 1, board, 2, circle2), 1)
        self.assertEqual(ai_service.find_horizontal_connection(5, 2, board, 2, circle2), 0)
        self.assertEqual(ai_service.find_horizontal_connection(5, 1, board, 4, circle2), 0)
        self.assertEqual(ai_service.find_diagonal_connection(5, 0, board, 3, circle1), 1)
        self.assertEqual(ai_service.find_diagonal_connection(5, 0, board, 4, circle1), 0)
        self.assertEqual(ai_service.find_diagonal_connection(4, 1, board, 3, circle1), 0)
        self.assertEqual(ai_service.find_diagonal_connection(5, 0, board, 2, circle1), 1)
        board_service.move(board, circle2, 3)
        self.assertEqual(ai_service.find_diagonal_connection(4, 2, board, 2, circle2), 1)
        self.assertEqual(ai_service.find_diagonal_connection(5, 3, board, 2, circle2), 0)
        self.assertEqual(ai_service.find_diagonal_connection(4, 2, board, 3, circle2), 0)
        self.assertEqual(ai_service.check_for_connection(board, circle1, 2), 2)
        self.assertEqual(ai_service.check_for_connection(board, circle2, 3), 1)
        self.assertEqual(ai_service.check_for_connection(board, circle1, 4), 0)
        self.assertEqual(ai_service.check_for_connection(board, circle1, 3), 1)
        self.assertEqual(ai_service.check_for_connection(board, circle2, 2), 5)
        self.assertEqual(ai_service.check_for_connection(board, circle2, 4), 0)
        self.assertEqual(ai_service.value(player2, board, circle2), 3)
        self.assertEqual(ai_service.value(player2, board, circle1), -3)
        self.assertEqual(ai_service.find(player2, 2, board, circle1), -105)
        self.assertEqual(ai_service.find(player2, 2, board, circle2), 100000)
        self.assertEqual(ai_service.move(player2, board), 4)
