class Solution {
public:
    int totalNQueens(int n) {
        vector<vector<int>> board(n, vector<int>(n, 0));
        return solveTotalNQueens(n, 0, board);
    }

    int solveTotalNQueens(int n, int row, vector<vector<int>>& board) {
        if (row == n) {
            return 1;
        }
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (isValid(board, row, i)) {
                board[row][i] = 1;
                count += solveTotalNQueens(n, row + 1, board);
                board[row][i] = 0;
            }
        }
        return count;
    }

    bool isValid (vector<vector<int>>& board, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) {
                return false;
            }
        }
        for (int i = 0; i < col; i++) {
            if (board[row][i] == 1) {
                return false;
            }
        }
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        return true;
    }
};