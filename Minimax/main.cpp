#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> board = {
    {"", "", ""},
    {"", "", ""},
    {"", "", ""}
};
string human = "O";
string ai = "X";
string currentPlayer = human;
map<string, int> scores = {
    {"X", 1},
    {"O", -1},
    {"tie", 0}
};

void print()
{
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == "")
                cout << " _ ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isEqual(string a, string b, string c)
{
    return ((a == b) && (b == c) && a != "");
}

string checkWinner()
{
    string winner = "";
    // Horizontal
    for (int i = 0; i < 3; i++)
    {
        if (isEqual(board[i][0], board[i][1], board[i][2]))
            winner = board[i][0];
    }

    // Vertical
    for (int i = 0; i < 3; i++)
    {
        if (isEqual(board[0][i], board[1][i], board[2][i]))
            winner = board[0][i];
    }

    // Diagonal
    if (isEqual(board[0][0], board[1][1], board[2][2]))
        winner = board[0][0];

    if (isEqual(board[2][0], board[1][1], board[0][2]))
        winner = board[2][0];

    int openSpots = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == "")
                openSpots++;
        }
    }
    if (winner.empty() && openSpots == 0)
        return "tie";

    return winner;
}

int minimax(vector<vector<string>> board, int depth, bool isMaximizing)
{
    string result = checkWinner();
    if (result != "")
    {
        return scores[result];
    }

    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == "")
                {
                    board[i][j] = ai;
                    int score = minimax(board, depth + 1, false);
                    board[i][j] = "";
                    bestScore = max(score, bestScore);
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == "")
                {
                    board[i][j] = human;
                    int score = minimax(board, depth + 1, true);
                    board[i][j] = "";
                    bestScore = min(score, bestScore);
                }
            }
        }

        return bestScore;
    }
}

void humanMove()
{
    int x, y;
    cout << "Enter row and column (space-separated): ";
    cin >> x >> y;

    // Input validation
    while (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != "")
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
        cin >> x >> y;
    }

    board[x][y] = human;
    currentPlayer = ai;
}

void aiMove()
{
    int bestScore = INT_MIN;
    pair<int, int> move;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == "")
            {
                board[i][j] = ai;
                int score = minimax(board, 0, false);
                board[i][j] = "";
                if (score > bestScore)
                {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }
    board[move.first][move.second] = ai;
    currentPlayer = human;
}

int main()
{
    string result = "";
    while (result == "" || result == "tie")
    {
        print();
        if (currentPlayer == human)
        {
            humanMove();
        }
        else
        {
            aiMove();
        }
        result = checkWinner();
    }
    print();
    cout << "Result: " << result << endl;

    return 0;
}
