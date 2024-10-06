#include <iostream>
using namespace std;

#define COMPUTER 'O'
#define HUMAN 'X'

// A function to show instructions for the players
void showInstructions() {
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n";
    cout << " 1 | 2 | 3 \n";
    cout << "-----------\n";
    cout << " 4 | 5 | 6 \n";
    cout << "-----------\n";
    cout << " 7 | 8 | 9 \n\n";
}

// A function to display the Tic-Tac-Toe board
void showBoard(char board[3][3]) {
    cout << "\nCurrent board state:\n\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if (j != 2) cout << " |";
        }
        cout << "\n";
        if (i != 2) cout << "-----------\n";
    }
    cout << "\n";
}

// A function to initialize the Tic-Tac-Toe board
void initialise(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '*';  // '*' denotes an empty cell
        }
    }
}

// A function to check if the human or computer has won by checking rows
bool rowCrossed(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

// A function to check if the human or computer has won by checking columns
bool columnCrossed(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}

// A function to check if the human or computer has won by checking diagonals
bool diagonalCrossed(char board[3][3]) {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;
    return false;
}

// A function to check if the game is over (either win or draw)
bool gameOver(char board[3][3]) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// A function to check if there are any moves left on the board
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '*')  // if there is an empty cell
                return true;
    return false;
}

// The Minimax function that considers all possible moves and returns the best move
int minimax(char board[3][3], int depth, bool isAI) {
    // Base cases for the minimax recursion
    if (rowCrossed(board)) return isAI ? -10 : 10;
    if (columnCrossed(board)) return isAI ? -10 : 10;
    if (diagonalCrossed(board)) return isAI ? -10 : 10;
    if (!isMovesLeft(board)) return 0;  // Draw

    if (isAI) {  // AI tries to maximize the score
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '*') {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isAI));
                    board[i][j] = '*';  // undo the move
                }
            }
        }
        return best;
    } else {  // Human tries to minimize the score
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '*') {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth + 1, !isAI));
                    board[i][j] = '*';  // undo the move
                }
            }
        }
        return best;
    }
}

// A function to find the best possible move for the computer (AI)
pair<int, int> findBestMove(char board[3][3]) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};  // stores the best move coordinates

    // Traverse all cells to find the best move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '*';  // undo the move

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Function to handle human and computer moves and run the game loop
void playTicTacToe() {
    char board[3][3];
    initialise(board);
    showInstructions();

    bool isHumanTurn = true;  // Human starts first
    while (!gameOver(board) && isMovesLeft(board)) {
        if (isHumanTurn) {
            int move;
            cout << "Your turn (choose a number 1-9): ";
            cin >> move;

            // Convert 1-9 input to 0-indexed board positions
            int x = (move - 1) / 3;
            int y = (move - 1) % 3;

            if (board[x][y] == '*') {
                board[x][y] = HUMAN;
                isHumanTurn = false;  // switch turn
            } else {
                cout << "Invalid move. Try again.\n";
            }
        } else {
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = COMPUTER;
            isHumanTurn = true;  // switch turn
        }
        showBoard(board);  // display board after every move
    }

    if (gameOver(board)) {
        if (isHumanTurn) {
            cout << "Computer wins!\n";
        } else {
            cout << "You win!\n";
        }
    } else {
        cout << "It's a draw!\n";
    }
}

int main() {
    playTicTacToe();
    return 0;
}
