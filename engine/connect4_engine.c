#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Connect4 {
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    vector<vector<char>> board;
    char aiStone;
    
    bool isValidMove(int col) {
        return col >= 0 && col < COLS && board[0][col] == '-';
    }
    
    int getLowestEmptyRow(int col) {
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == '-') {
                return row;
            }
        }
        return -1;
    }
    
    bool checkWin(int row, int col, char stone) {
        // Check horizontal
        for (int c = 0; c <= COLS - 4; c++) {
            if (board[row][c] == stone && board[row][c+1] == stone && 
                board[row][c+2] == stone && board[row][c+3] == stone) {
                return true;
            }
        }
        
        // Check vertical
        for (int r = 0; r <= ROWS - 4; r++) {
            if (board[r][col] == stone && board[r+1][col] == stone && 
                board[r+2][col] == stone && board[r+3][col] == stone) {
                return true;
            }
        }
        
        // Check diagonal (top-left to bottom-right)
        for (int r = 0; r <= ROWS - 4; r++) {
            for (int c = 0; c <= COLS - 4; c++) {
                if (board[r][c] == stone && board[r+1][c+1] == stone && 
                    board[r+2][c+2] == stone && board[r+3][c+3] == stone) {
                    return true;
                }
            }
        }
        
        // Check diagonal (top-right to bottom-left)
        for (int r = 0; r <= ROWS - 4; r++) {
            for (int c = 3; c < COLS; c++) {
                if (board[r][c] == stone && board[r+1][c-1] == stone && 
                    board[r+2][c-2] == stone && board[r+3][c-3] == stone) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    int evaluatePosition() {
        int score = 0;
        char opponent = (aiStone == 'X') ? 'O' : 'X';
        
        // Evaluate for AI
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (board[row][col] == aiStone) {
                    score += 10;
                } else if (board[row][col] == opponent) {
                    score -= 10;
                }
            }
        }
        
        return score;
    }
    
    int minimax(int depth, bool isMaximizing, int alpha, int beta) {
        if (depth == 0) {
            return evaluatePosition();
        }
        
        if (isMaximizing) {
            int maxEval = -1000;
            for (int col = 0; col < COLS; col++) {
                if (isValidMove(col)) {
                    int row = getLowestEmptyRow(col);
                    board[row][col] = aiStone;
                    
                    if (checkWin(row, col, aiStone)) {
                        board[row][col] = '-';
                        return 1000;
                    }
                    
                    int eval = minimax(depth - 1, false, alpha, beta);
                    board[row][col] = '-';
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) break;
                }
            }
            return maxEval;
        } else {
            int minEval = 1000;
            char opponent = (aiStone == 'X') ? 'O' : 'X';
            for (int col = 0; col < COLS; col++) {
                if (isValidMove(col)) {
                    int row = getLowestEmptyRow(col);
                    board[row][col] = opponent;
                    
                    if (checkWin(row, col, opponent)) {
                        board[row][col] = '-';
                        return -1000;
                    }
                    
                    int eval = minimax(depth - 1, true, alpha, beta);
                    board[row][col] = '-';
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) break;
                }
            }
            return minEval;
        }
    }
    
public:
    Connect4(char stone) : aiStone(stone) {
        board = vector<vector<char>>(ROWS, vector<char>(COLS, '-'));
    }
    
    void readBoard() {
        for (int row = 0; row < ROWS; row++) {
            string line;
            getline(cin, line);
            for (int col = 0; col < COLS; col++) {
                board[row][col] = line[col * 2]; // Skip spaces
            }
        }
    }
    
    int findBestMove() {
        int bestMove = -1;
        int bestValue = -1000;
        
        for (int col = 0; col < COLS; col++) {
            if (isValidMove(col)) {
                int row = getLowestEmptyRow(col);
                board[row][col] = aiStone;
                
                int moveValue = minimax(4, false, -1000, 1000);
                board[row][col] = '-';
                
                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = col;
                }
            }
        }
        
        return bestMove + 1; // Convert to 1-based indexing
    }
};

int main(int argc, char* argv[]) {
    char aiStone = 'O'; // Default
    
    if (argc > 1) {
        string stone = argv[1];
        if (stone == "X" || stone == "O") {
            aiStone = stone[0];
        }
    }
    
    Connect4 game(aiStone);
    game.readBoard();
    
    int move = game.findBestMove();
    cout << move << endl;
    
    return 0;
}
