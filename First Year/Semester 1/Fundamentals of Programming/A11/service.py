from domain import Board


class BoardService:
    def is_game_won(self, board):
        """
        Checks if the game was won by a player or the computer
        :return: True if the game was won, False otherwise
        """
        for row in range(6):
            for column in range(4):
                if board.matrix[row][column] != '●':
                    if board.matrix[row][column] == board.matrix[row][column + 1]:
                        if board.matrix[row][column] == board.matrix[row][column + 2]:
                            if board.matrix[row][column] == board.matrix[row][column + 3]:
                                return True
        for column in range(7):
            for row in range(3):
                if board.matrix[row][column] != '●':
                    if board.matrix[row][column] == board.matrix[row + 1][column]:
                        if board.matrix[row][column] == board.matrix[row + 2][column]:
                            if board.matrix[row][column] == board.matrix[row + 3][column]:
                                return True
        for row in range(3):
            for column in range(4):
                if board.matrix[row][column] != '●':
                    if board.matrix[row][column] == board.matrix[row + 1][column + 1]:
                        if board.matrix[row][column] == board.matrix[row + 2][column + 2]:
                            if board.matrix[row][column] == board.matrix[row + 3][column + 3]:
                                return True
        for row in range(3):
            column = 6
            while column >= 3:
                if board.matrix[row][column] != '●':
                    if board.matrix[row][column] == board.matrix[row + 1][column - 1]:
                        if board.matrix[row][column] == board.matrix[row + 2][column - 2]:
                            if board.matrix[row][column] == board.matrix[row + 3][column - 3]:
                                return True
                column -= 1
        return False

    def is_draw(self, board):
        """
        Checks if the game is a draw
        :return: True if the game is a draw and False otherwise
        """
        for row in range(6):
            for column in range(7):
                if board.matrix[row][column] == '●':
                    return False
        return True

    def move(self, board, circle, column):
        """
        Method that enables a move on the board
        :param board: the current state of the board
        :param circle: the colour of the circle
        :param column: the column in which the circle will be introduced
        :return: True if the move is possible on that column, false otherwise
        """
        i = 5
        while i > -1:
            if board.matrix[i][column] == '●':
                board.matrix[i][column] = circle
                return True
            i -= 1
        return False


class AIService:
    def is_legal_move(self, board, column):
        """
        Checks if the move is legal for a given state of a board and a column
        :param board: -
        :param column: -
        :return: True if the move is legal, False otherwise
        """
        i = 5
        while i > -1:
            if board.matrix[i][column] == '●':
                return True
            i -= 1
        return False

    def simulate_move(self, board, column, circle):
        """
        Simulates a move for the minimax algorithm
        :param board: the state of the board before the simulated move
        :param column: the column in which the move will be made
        :param circle: the circle to be introduced in the board
        :return: a virtual board in which the move was made
        """
        board2 = Board()
        for i in range(6):
            for j in range(7):
                board2.matrix[i][j] = board.matrix[i][j]
        BoardService().move(board2, circle, column)
        return board2

    def move(self, ai, board):
        """
        Searches for the best move for a given state of the board
        :param ai: the computer
        :param board: the state of the board
        :return: the best move as a column number
        """
        legal_moves = {}
        for i in range(7):
            if self.is_legal_move(board, i) is True:
                board2 = self.simulate_move(board, i, ai.circle)
                legal_moves[i] = -self.find(ai, ai.difficulty - 1, board2, ai.opponent_circle)
        best_score = -99999999
        best_move = None
        moves = legal_moves.items()
        for move, score in moves:
            if score > best_score:
                best_score = score
                best_move = move
        return best_move

    def find(self, ai, depth, board, circle):
        """
        Finds the score of a move by recursively completing
        a virtual board until the depth parameter reaches 0
        :param ai: the computer
        :param depth: the "depth" at which the board will be populated with moves
        :param board: the state of the board to find the score of a certain move
        :param circle: the circle of the certain move
        :return: the score of the move calculated using an heuristic
        """
        legal_moves = []
        for i in range(7):
            if self.is_legal_move(board, i):
                board2 = self.simulate_move(board, i, circle)
                legal_moves.append(board2)
        if depth == 0 or len(legal_moves) == 0 or BoardService().is_game_won(board):
            return self.value(ai, board, circle)
        if circle == ai.circle:
            opponent_circle = ai.opponent_circle
        else:
            opponent_circle = ai.circle
        score = -99999999
        for i in legal_moves:
            score = max(score, -self.find(ai, depth - 1, i, opponent_circle))
        return score

    def value(self, ai, board, circle):
        """
        Calculates the value for a configuration of the table using a certain heuristic
        :param ai: the computer
        :param board: -
        :param circle: -
        :return: the score of a configuration of the table
        """
        if circle == ai.circle:
            opponent_circle = ai.opponent_circle
        else:
            opponent_circle = ai.circle
        m_fours = self.check_for_connection(board, circle, 4)
        m_threes = self.check_for_connection(board, circle, 3)
        m_twos = self.check_for_connection(board, circle, 2)
        o_fours = self.check_for_connection(board, opponent_circle, 4)
        o_threes = self.check_for_connection(board, opponent_circle, 3)
        o_twos = self.check_for_connection(board, opponent_circle, 2)
        if o_fours > 0:
            return -100000
        else:
            return m_fours*100000 + m_threes*100 + m_twos - o_threes*100 - o_twos

    def check_for_connection(self, board, circle, length):
        """
        Calculates the number of connections of certain length for
        a configuration of the board, for a certain player
        :param board: the configuration of the table
        :param circle: the circle of the player
        :param length: he length of the connections to be looked for
        :return: the number of connections
        """
        count = 0
        for i in range(6):
            for j in range(7):
                if board.matrix[i][j] == circle:
                    count += self.find_vertical_connection(i, j, board, length, board.matrix[i][j])
                    count += self.find_horizontal_connection(i, j, board, length, board.matrix[i][j])
                    count += self.find_diagonal_connection(i, j, board, length, board.matrix[i][j])
        return count

    def find_vertical_connection(self, i, j, board, length, circle):
        """
        Calculates the number of vertical connections for a certain position
        :param i: the height of the position
        :param j: the width of the position
        :param board: the state of the board
        :param length: the length of the connections needed
        :param circle: the connections which are looked for need to be of this circle
        :return: the number of the connections found with all the characteristics mentioned
        """
        count = 0
        if i + length - 1 < 6:
            for x in range(length):
                if board.matrix[i + x][j] == circle:
                    count += 1
                else:
                    break
        if count == length:
            return 1
        else:
            return 0

    def find_horizontal_connection(self, i, j, board, length, circle):
        """
        Calculates the number of horizontal connections for a certain position
        :param i: the height of the position
        :param j: the width of the position
        :param board: the state of the board
        :param length: the length of the connections needed
        :param circle: the connections which are looked for need to be of this circle
        :return: the number of the connections found with all the characteristics mentioned
        """
        count = 0
        if j + length - 1 < 7:
            for x in range(length):
                if circle == board.matrix[i][j + x]:
                    count += 1
                else:
                    break
        if count == length:
            return 1
        else:
            return 0

    def find_diagonal_connection(self, i, j, board, length, circle):
        """
        Calculates the number of diagonal connections for a certain position
        :param i: the height of the position
        :param j: the width of the position
        :param board: the state of the board
        :param length: the length of the connections needed
        :param circle: the connections which are looked for need to be of this circle
        :return:
        """
        total = 0
        count = 0
        if j + length - 1 < 7 and i + length - 1 < 6:
            for x in range(length):
                if circle == board.matrix[i + x][j + x]:
                    count += 1
                else:
                    break
        if count == length:
            total += 1
        count = 0
        if j + length - 1 < 7 and i - length + 1 > -1:
            for x in range(length):
                if circle == board.matrix[i - x][j + x]:
                    count += 1
                else:
                    break
        if count == length:
            total += 1
        return total
