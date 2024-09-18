#include <bits/stdc++.h>

using namespace std;

// Map piece characters to their corresponding values
map<char, int> PIECE_DICT = {{'Q', 4}, {'R', 3}, {'B', 2}, {'N', 1}};

// Map board positions (e.g., "A1") to their corresponding indices in the board array
map<char, map<int, int>> BOARD_DICT = {
    {'A', {{"1", 0}, {"2", 1}, {"3", 2}, {"4", 3}}},
    {'B', {{"1", 4}, {"2", 5}, {"3", 6}, {"4", 7}}},
    {'C', {{"1", 8}, {"2", 9}, {"3", 10}, {"4", 11}}},
    {'D', {{"1", 12}, {"2", 13}, {"3", 14}, {"4", 15}}}
};

// List of possible move directions
vector<string> MOVE_LIST = {"r", "d", "l", "u", "dr", "dl", "ur", "ul"};

// Map move directions to their corresponding index changes for each board position
map<string, vector<int>> MOVE_DICT;

// Initialize the board based on the input
vector<int> get_init_board(int n_white, int n_black) {
    vector<int> board(16, 0); // Initialize all board positions to 0

    for (int i = 0; i < n_white + n_black; ++i) {
        char pc;
        string row, col;
        cin >> pc >> row >> col;

        int piece = PIECE_DICT[pc] * (i < n_white ? 1 : -1); // Positive for white, negative for black
        int position = BOARD_DICT[row[0]][col]; 
        board[position] = piece;
    }

    return board;
}

// Precompute valid move directions for each position on the board
void precompute_moves() {
    for (int i = 0; i < 16; ++i) {
        bool ok_right = (i % 4 != 3);
        bool ok_left = (i % 4 != 0);
        bool ok_up = (i >= 4);
        bool ok_down = (i <= 11);

        if (ok_right) MOVE_DICT["r"][i] = i + 1;
        if (ok_left)  MOVE_DICT["l"][i] = i - 1;
        if (ok_down)  MOVE_DICT["d"][i] = i + 4;
        if (ok_up)    MOVE_DICT["u"][i] = i - 4;

        if (ok_right && ok_down) MOVE_DICT["dr"][i] = i + 5;
        if (ok_left && ok_down)  MOVE_DICT["dl"][i] = i + 3;
        if (ok_right && ok_up)   MOVE_DICT["ur"][i] = i - 3;
        if (ok_left && ok_up)    MOVE_DICT["ul"][i] = i - 5;
    }
}

// Determine valid knight moves
void knight_moves(const vector<int>& board, int i, vector<vector<int>>& result_boards) {
    for (int s = 0; s < 4; ++s) {
        int j = MOVE_DICT[MOVE_LIST[s]][i];
        if (j == -1) continue;

        j = MOVE_DICT[MOVE_LIST[s]][j];
        if (j == -1) continue;

        for (int t = 0; t < 2; ++t) {
            int tt = (s + 2 * t + 1) % 4;
            int k = MOVE_DICT[MOVE_LIST[tt]][j];
            if (k == -1) continue;

            if (board[k] <= 0) { // Empty or opponent's piece
                vector<int> new_board = board;
                new_board[i] = 0;
                new_board[k] = 1;
                result_boards.push_back(new_board);
            }
        }
    }
}

// Determine valid single-directional moves (for all pieces except knights)
void directional_moves(const vector<int>& board, int i, const string& direction, vector<vector<int>>& result_boards) {
    int pos = i;
    while (true) {
        pos = MOVE_DICT[direction][pos];
        if (pos == -1) return; 

        if (board[pos] > 0) return; // Blocked by own piece

        vector<int> new_board = board;
        new_board[pos] = new_board[i];
        new_board[i] = 0;
        result_boards.push_back(new_board);

        if (board[pos] < 0) return; // Captured opponent's piece
    }
}

// Determine valid bishop moves
void bishop_moves(const vector<int>& board, int i, vector<vector<int>>& result_boards) {
    for (int d = 4; d < 8; ++d) { // Diagonal move directions
        directional_moves(board, i, MOVE_LIST[d], result_boards);
    }
}

// Determine valid rook moves
void rook_moves(const vector<int>& board, int i, vector<vector<int>>& result_boards) {
    for (int d = 0; d < 4; ++d) { // Horizontal/vertical move directions
        directional_moves(board, i, MOVE_LIST[d], result_boards);
    }
}

// Determine valid queen moves
void queen_moves(const vector<int>& board, int i, vector<vector<int>>& result_boards) {
    for (const string& d : MOVE_LIST) { 
        directional_moves(board, i, d, result_boards);
    }
}

// Generate all possible new boards after one move
vector<vector<int>> generate_new_boards(const vector<int>& board) {
    vector<vector<int>> result_boards;

    for (int i = 0; i < 16; ++i) {
        if (board[i] == 1)  knight_moves(board, i, result_boards);    // Knight
        if (board[i] == 2)  bishop_moves(board, i, result_boards);    // Bishop
        if (board[i] == 3)  rook_moves(board, i, result_boards);      // Rook
        if (board[i] == 4)  queen_moves(board, i, result_boards);      // Queen
    }

    return result_boards;
}

// Check if the current board represents a win for white
bool is_win(const vector<int>& board) {
    for (int p : board) {
        if (p == -4) { // Black queen still exists
            return false;
        }
    }
    return true;
}

// Memoization to store already computed board values
map<tuple<vector<int>, int>, int> memo;

// Evaluate the board's value for white at a given depth
int board_value(const vector<int>& board, int depth) {
    tuple<vector<int>, int> state = make_tuple(board, depth);
    if (memo.count(state)) {
        return memo[state];
    }

    if (depth == 0) {
        return 0; // Reached maximum depth, no clear win/loss
    }

    vector<vector<int>> possible_boards = generate_new_boards(board);
    if (possible_boards.empty()) {
        return 0; // No possible moves, stalemate
    }

    for (const vector<int>& new_board : possible_boards) {
        if (is_win(new_board)) {
            memo[state] = 1; // White can win in this position
            return 1;
        }
    }

    int best = -1;
    for (const vector<int>& new_board : possible_boards) {
        vector<int> opponent_board(new_board.size());
        for (size_t i = 0; i < new_board.size(); ++i) {
                    opponent_board[i] = -new_board[i]; // Negate the board for the opponent's perspective
        }

        int v = -board_value(opponent_board, depth - 1); // Evaluate from the opponent's perspective
        if (v > best) {
            best = v;
        }
        if (best == 1) {
            break; // White can force a win, no need to check further
        }
    }

    memo[state] = best;
    return best;
}