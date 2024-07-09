#include <iostream>
using namespace std;

#define N 10
#define M 10

class CaroGame {
public:
    int board[N][M];
    int n;
    int m;
    int player;
    int opponent;

    CaroGame(int n, int m) {
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                board[i][j] = 0;
            }
        }
        player = 1;
        opponent = 2;
    }

    void printBoard() {
        //implement this
    }

    bool isMoveValid(int x, int y) {
       //implement this
    }

    bool isWin(int x, int y) {
       //implement this
    }

    bool tick(int x, int y) {
       //implement this
    }

    void run() {
        while (true) {
            printBoard();
            cout << "Player " << player << " input move:" << endl;
            int x, y;
            cin >> x >> y;

            if (isMoveValid(x, y)) {
                bool isEndGame = tick(x, y);
                if (isEndGame) {
                    printBoard();
                    break;
                }
            } else {
                cout << "Invalid move" << endl;
            }
        }
    }
};

int main() {
    CaroGame caroGame(10, 10);
    caroGame.run();
    return 0;
}

