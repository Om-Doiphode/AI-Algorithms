#include <bits/stdc++.h>
using namespace std;

// AI is the maximizing player
string human = "O";
string ai = "X";
string currentPlayer = human;
map<string, int> scores = {
    {"X", 1},
    {"O", -1},
    {"tie", 0}
};

void showBoard(vector<vector<string>>board) 
{ 
	
	cout<<"\t\t\t"<<board[0][0]<<" | "<< board[0][1]<<" | "<< board[0][2]<<endl;
    cout<<("\t\t\t-----------")<<endl;
    cout<<"\t\t\t"<<board[1][0]<<" | "<< board[1][1]<<" | "<< board[1][2]<<endl;
	cout<<("\t\t\t-----------")<<endl; 
    cout<<"\t\t\t"<<board[2][0]<<" | "<< board[2][1]<<" | "<< board[2][2]<<endl; 
}
void showInstructions() 
{ 
	printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
}
bool isEqual(string a, string b, string c)
{
    return ((a == b) && (b == c) && a != "");
}

string checkWinner(vector<vector<string>>board)
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
    string result = checkWinner(board);
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
int bestMove(vector<vector<string>>board,int idx)
{
    int x=-1,y=-1;
    int score=0,bestScore=INT_MIN;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]=="")
            {
                board[i][j]=ai;
                score=minimax(board,idx+1,false);
                board[i][j]="";
                if(score>bestScore)
                {
                    bestScore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
}
void play(int turn)
{
    vector<vector<string>> board = {
        {"", "", ""},
        {"", "", ""},
        {"", "", ""}
        };
    int moveIdx=0,x=0,y=0;
    showInstructions();

    while(checkWinner(board).empty() && moveIdx!=9)
    {
        int n;
        if(turn==scores[ai])
        {
            n=bestMove(board,moveIdx);

            x=n/3;
            y=n%3;
            board[x][y]=ai;
            cout<<"Computer move: "<<endl;
            showBoard(board);
            moveIdx++;
            turn=scores[human];
        }
        else if(turn==scores[human])
        {
            cout<<"Empty Positions available: "<<endl;
            for(int i=0;i<board.size();i++)
            {
                for(int j=0;j<board.size();j++)
                {
                    if(board[i][j]=="")
                        cout<<(i*3+j)+1<<" ";
                }
            }
            cout<<"\nEnter the position: ";
            cin>>n;
            n--;
            x=n/3;
            y=n%3;

            if(board[x][y]=="" && n<9 && n>=0)
            {
                board[x][y]=human;
                cout<<"Your move: "<<endl;
                showBoard(board);
                moveIdx++;
                turn=scores[ai];
            }
            else if(board[x][y]!="" && n<9 && n>=0)
            {
                cout<<"Position is occupied, select any one place from the available positions"<<endl;
            }
            else
            {
                cout<<"Invalid position"<<endl;
            }
        }
    }
    if(checkWinner(board)=="tie")
    {
        cout<<"It is a tie"<<endl;
    }
    else
    {
        cout<<((checkWinner(board)=="X")?"COMPUTER":"YOU")<<" WON"<<endl;
    }
    
}
int main()
{
    cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t Tic-Tac-Toe"<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
    char cont='y';
    do{
        char choice;
        cout<<"Do you want to start first? (y/n): ";
        cin>>choice;

        if(choice=='n')
        {
            play(scores[ai]);
        }
        else if(choice=='y')
        {
            play(scores[human]);
        }
        else
        {
            cout<<"Invalid choice"<<endl;
        }

        cout<<"Do you want to quit? (y/n): ";
        cin>>cont;
    }while(cont=='n');
}
