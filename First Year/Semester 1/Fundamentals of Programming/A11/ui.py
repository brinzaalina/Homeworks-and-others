from domain import Circle, Player, Board, AI
from service import BoardService, AIService


class UI:
    def __init__(self, board_service, ai_service):
        self.board_service = board_service
        self.ai_service = ai_service

    @staticmethod
    def print_menu():
        print("Available game modes:")
        print("1. Human vs. Human")
        print("2. Human vs. Computer")
        print("0. Exit")

    @staticmethod
    def check_column_integer(message):
        if message.isdigit():
            column = int(message)
            if 0 < column < 8:
                return True
        return False

    def human_vs_computer(self):
        circle_1 = Circle("yellow")
        circle_2 = Circle("magenta")
        name = input("Enter your name: ")
        player1 = Player(name, circle_1)
        player2 = AI(circle_2, circle_1, 4)
        board = Board()
        print(player1)
        print(player2)
        print(board)
        while self.board_service.is_draw(board) is False:
            column1 = input(player1.get_name + ", choose the column for your move: ")
            while self.check_column_integer(column1) is False:
                column1 = input("Invalid column number, please choose a number between 1 and 7: ")
            column1 = int(column1)
            column1 -= 1
            while self.board_service.move(board, player1.get_circle, column1) is False:
                column1 = input("Please choose a column which is not full: ")
                while self.check_column_integer(column1) is False:
                    column1 = input("Invalid column number, please choose a number between 1 and 7: ")
                column1 = int(column1)
                column1 -= 1
            print(board)
            if self.board_service.is_game_won(board) is False:
                print("The computer is thinking...")
                column2 = int(self.ai_service.move(player2, board))
                print("The computer chose the column {}.".format(str(column2 + 1)))

                self.board_service.move(board, player2.get_circle, column2)
                print(board)
                if self.board_service.is_game_won(board) is True:
                    print("The computer won!")
                    break
                continue
            print("{} won!".format(player1.get_name))
            break
        if self.board_service.is_draw(board) is True:
            print("Draw!")

    def human_vs_human(self):
        circle1 = Circle("yellow")
        circle2 = Circle("magenta")
        name1 = input("Enter the name for the first player: ")
        name2 = input("Enter the name for the second player: ")
        player1 = Player(name1, circle1)
        player2 = Player(name2, circle2)
        board = Board()
        print(player1)
        print(player2)
        print(board)
        while self.board_service.is_draw(board) is False:
            column1 = input("{}, choose the column for your move: ".format(player1.get_name))
            while self.check_column_integer(column1) is False:
                column1 = input("Invalid column number, please choose a number between 1 and 7: ")
            column1 = int(column1)
            column1 -= 1
            while self.board_service.move(board, player1.get_circle, column1) is False:
                column1 = input("Please choose a column which is not full: ")
                while self.check_column_integer(column1) is False:
                    column1 = input("Invalid column number, please choose a number between 1 and 7: ")
                column1 = int(column1)
                column1 -= 1
            print(board)
            if self.board_service.is_game_won(board) is False:
                column2 = input("{}, choose the column for your move: ".format(player2.get_name))
                while self.check_column_integer(column2) is False:
                    column2 = input("Invalid column number, please choose a number between 1 and 7: ")
                column2 = int(column2)
                column2 -= 1
                while self.board_service.move(board, player2.get_circle, column2) is False:
                    column2 = input("Please choose a column which is not full: ")
                    while self.check_column_integer(column2) is False:
                        column2 = input("Invalid column number, please choose a number between 1 and 7: ")
                    column2 = int(column2)
                    column2 -= 1
                print(board)
                if self.board_service.is_game_won(board) is True:
                    print("{} won!".format(player2.get_name))
                    break
                continue
            print("{} won!".format(player1.get_name))
            break
        if self.board_service.is_draw(board) is True:
            print("Draw!")

    def menu(self):
        done = False
        while not done:
            UI.print_menu()
            command = input("Choose an option: ")
            if command == '1':
                self.human_vs_human()
            elif command == '2':
                self.human_vs_computer()
            elif command == '0':
                done = True


board_service = BoardService()
ai_service = AIService()
Game = UI(board_service, ai_service)
Game.menu()
