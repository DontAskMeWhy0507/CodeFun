class CaroGame:
    def __init__(self, n, m):
        self.n = n
        self.m = m
        self.board = [[0] * m for _ in range(n)]
        self.player = 1
        self.opponent = 2

    def print_board(self):
        for row in self.board:
            print(' '.join(str(cell) for cell in row))

    def is_move_valid(self, x, y):
        return 0 <= x < self.n and 0 <= y < self.m and self.board[x][y] == 0

    def is_win(self, x, y):
        directions = [(0, 1), (1, 0), (1, 1), (1, -1)]
        for dx, dy in directions:
            count = 1
            for i in range(1, 5):
                nx, ny = x + dx*i, y + dy*i
                if 0 <= nx < self.n and 0 <= ny < self.m and self.board[nx][ny] == self.player:
                    count += 1
                else:
                    break
            for i in range(1, 5):
                nx, ny = x - dx*i, y - dy*i
                if 0 <= nx < self.n and 0 <= ny < self.m and self.board[nx][ny] == self.player:
                    count += 1
                else:
                    break
            if count >= 5:
                return True
        return False

    def tick(self, x, y):
        self.board[x][y] = self.player
        if self.is_win(x, y):
            print(f"Player {self.player} wins!")
            return True
        self.player, self.opponent = self.opponent, self.player
        return False

    def run(self):
        while True:
            self.print_board()
            print(f"Player {self.player}'s turn. Input move (row col):")
            x, y = map(int, input().split())

            if self.is_move_valid(x, y):
                if self.tick(x, y):
                    self.print_board()
                    break
            else:
                print("Invalid move. Try again.")