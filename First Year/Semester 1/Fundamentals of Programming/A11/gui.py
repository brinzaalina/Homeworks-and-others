import tkinter as tk
from tkinter import simpledialog

from termcolor import colored

from domain import Circle, Player, Board, AI
from service import BoardService, AIService


class GUI:
    def __init__(self, board_service, ai_service):
        self.board_service = board_service
        self.ai_service = ai_service
        self._window = tk.Tk()
        self._window.configure(bg='#A96DA3')

    def start(self):
        self._window.title("CONNECT FOUR")
        btn_human_vs_human = tk.Button(master=self._window, text='Human vs. Human', bg='#FFDDE2', command=self.human_vs_human)
        btn_human_vs_human.pack()
        btn_human_vs_computer = tk.Button(master=self._window, text='Human vs. Computer', bg='#FFDDE2', command=self.human_vs_computer)
        btn_human_vs_computer.pack()
        btn_exit = tk.Button(master=self._window, text='Exit', bg='#FFDDE2', command=self._window.destroy)
        btn_exit.pack()
        self._window.mainloop()

    @staticmethod
    def check_column_integer(message):
        if message.isdigit():
            column = int(message)
            if 0 < column < 8:
                return True
        return False

    def human_vs_human(self):
        circle1 = Circle("yellow")
        circle2 = Circle("magenta")
        name1 = simpledialog.askstring(title="-1st player-", prompt="Enter your name:")
        name2 = simpledialog.askstring(title="-2nd player-", prompt="Enter your name:")
        player1 = Player(name1, circle1)
        player2 = Player(name2, circle2)
        board = Board()
        scroll_bar = tk.Scrollbar(self._window)
        scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)
        scroll_text = tk.Text(master=self._window, height=50, width=200)
        scroll_text.pack(side=tk.LEFT, fill=tk.Y)
        scroll_bar.config(command=scroll_text.yview)
        scroll_text.config(yscrollcommand=scroll_bar.set)
        text = str(player1).replace(colored('●', 'yellow'), 'yellow ●') + "\n" + str(player2).replace(colored('●', 'magenta'), 'magenta ●') + "\n" + str(board) + "\n"
        scroll_text.insert(tk.END, text)
        while self.board_service.is_draw(board) is False:
            column1 = simpledialog.askstring(title="-move-", prompt="{}, choose a column:".format(player1.get_name))
            while self.check_column_integer(column1) is False:
                column1 = simpledialog.askstring(title="-move-", prompt="Invalid number, choose a value between 1 and 7: ")
            column1 = int(column1)
            column1 -= 1
            while self.board_service.move(board, player1.get_circle, column1) is False:
                column1 = simpledialog.askstring(title="-move-", prompt="Choose a non-full column: ")
                while self.check_column_integer(column1) is False:
                    column1 = simpledialog.askstring(title="-move-", prompt="Invalid number, choose between 1 and 7: ")
                column1 = int(column1)
                column1 -= 1
            text = str(board).replace(colored('●', 'yellow'), 'y').replace(colored('●', 'magenta'), 'm') + "\n"
            scroll_text.insert(tk.END, text)
            if self.board_service.is_game_won(board) is False:
                column2 = simpledialog.askstring(title="-move-", prompt="{}, choose a column:".format(player2.get_name))
                while self.check_column_integer(column2) is False:
                    column2 = simpledialog.askstring(title="-move-", prompt="Invalid column number, choose between 1 and 7: ")
                column2 = int(column2)
                column2 -= 1
                while self.board_service.move(board, player2.get_circle, column2) is False:
                    column2 = simpledialog.askstring(title="-move-", prompt="Choose a column which is not full : ")
                    while self.check_column_integer(column2) is False:
                        column2 = simpledialog.askstring(title="-move-", prompt="Invalid column number, choose between 1 and 7: ")
                    column2 = int(column2)
                    column2 -= 1
                text = str(board).replace(colored('●', 'yellow'), 'y').replace(colored('●', 'magenta'), 'm') + "\n"
                scroll_text.insert(tk.END, text)
                if self.board_service.is_game_won(board) is True:
                    text = "{} won! \n".format(player2.get_name)
                    scroll_text.insert(tk.END, text)
                    break
                continue
            text = "{} won!\n".format(player1.get_name)
            scroll_text.insert(tk.END, text)
            break
        if self.board_service.is_draw(board) is True:
            text = "Draw!\n"
            scroll_text.insert(tk.END, text)

    def human_vs_computer(self):
        circle1 = Circle("yellow")
        circle2 = Circle("magenta")
        name = simpledialog.askstring(title="-1st player-", prompt="Enter your name:")
        player1 = Player(name, circle1)
        player2 = AI(circle2, circle1, 4)
        board = Board()
        scroll_bar = tk.Scrollbar(self._window)
        scroll_bar.pack(side=tk.RIGHT, fill=tk.Y)
        scroll_text = tk.Text(master=self._window, height=40, width=150)
        scroll_text.pack(side=tk.LEFT, fill=tk.Y)
        scroll_bar.config(command=scroll_text.yview)
        scroll_text.config(yscrollcommand=scroll_bar.set)
        text = str(player1).replace(colored('●', 'yellow'), 'yellow ●') + "\n" + str(player2).replace(colored('●', 'magenta'), 'magenta ●') + "\n" + str(board) + "\n"
        scroll_text.insert(tk.END, text)
        while self.board_service.is_draw(board) is False:
            column1 = simpledialog.askstring(title="-move-", prompt="{}, choose a column:".format(player1.get_name))
            while self.check_column_integer(column1) is False:
                column1 = simpledialog.askstring(title="-move-", prompt="Invalid number, choose a value between 1 and 7: ")
            column1 = int(column1)
            column1 -= 1
            while self.board_service.move(board, player1.get_circle, column1) is False:
                column1 = simpledialog.askstring(title="-move-", prompt="Choose a non-full column: ")
                while self.check_column_integer(column1) is False:
                    column1 = simpledialog.askstring(title="-move-", prompt="Invalid number, choose between 1 and 7: ")
                column1 = int(column1)
                column1 -= 1
            text = str(board).replace(colored('●', 'yellow'), 'y').replace(colored('●', 'magenta'), 'm') + "\n"
            scroll_text.insert(tk.END, text)
            if self.board_service.is_game_won(board) is False:
                text = "The computer is thinking ... \n"
                scroll_text.insert(tk.END, text)
                column2 = int(self.ai_service.move(player2, board))
                text = "The computer chose the column {} \n".format(str(column2 + 1))
                scroll_text.insert(tk.END, text)
                self.board_service.move(board, player2.get_circle, column2)
                text = str(board).replace(colored('●', 'yellow'), 'y').replace(colored('●', 'magenta'), 'm') + "\n"
                scroll_text.insert(tk.END, text)
                if self.board_service.is_game_won(board) is True:
                    text = "The computer won! \n"
                    scroll_text.insert(tk.END, text)
                    break
                continue
            text = "{} won!\n".format(player1.get_name)
            scroll_text.insert(tk.END, text)
            break
        if self.board_service.is_draw(board) is True:
            text = "Draw!\n"
            scroll_text.insert(tk.END, text)


board_service = BoardService()
ai_service = AIService()
GUI(board_service, ai_service).start()
