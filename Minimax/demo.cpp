#include <iostream>
#include <limits>

const int SIZE = 3;

char board[SIZE][SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char human = 'O';
char ai = 'X';

void printBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j];
            if (j < SIZE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < SIZE - 1) {
            std::cout << "---------" << std::endl;
        }
    }
    std::cout << std::endl;
}

bool isBoardFull() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool isValidMove(int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

bool checkWinner(char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
        return true;
    }

    return false;
}

bool makeMove(int row, int col, char player) {
    if (isValidMove(row, col)) {
        board[row][col] = player;
        return true;
    }
    return false;
}

void humanMove() {
    int row, col;
    std::cout << "Enter your move (row and column): ";
    std::cin >> row >> col;

    while (!makeMove(row, col, human)) {
        std::cout << "Invalid move. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> row >> col;
    }
}

void aiMove() {
    // Placeholder for AI move - you can replace this with the minimax algorithm
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!makeMove(row, col, ai));
}

int main() {
    srand(time(NULL));

    while (true) {
        printBoard();

        // Human's turn
        humanMove();

        if (checkWinner(human)) {
            printBoard();
            std::cout << "You win!" << std::endl;
            break;
        }

        if (isBoardFull()) {
            printBoard();
            std::cout << "It's a tie!" << std::endl;
            break;
        }

        // AI's turn
        aiMove();

        if (checkWinner(ai)) {
            printBoard();
            std::cout << "AI wins!" << std::endl;
            break;
        }

        if (isBoardFull()) {
            printBoard();
            std::cout << "It's a tie!" << std::endl;
            break;
        }
    }

    return 0;
}
