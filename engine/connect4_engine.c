#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7

void read_board(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int c = getchar();
            while (c == ' ' || c == '\n') c = getchar();
            if (c == '-') board[i][j] = ' ';
            else board[i][j] = (char)c;
        }
        // skip to end of line
        while (1) {
            int c = getchar();
            if (c == '\n' || c == EOF) break;
        }
    }
}

int is_valid_move(char board[ROWS][COLS], int col) {
    if (col < 0 || col >= COLS) return 0;
    // If the top cell is not empty, column is full
    if (board[0][col] != '-') return 0;
    return 1;
}

// Function to validate a Connect 4 board read from stdin
bool isValidConnect4BoardFromStdin(char board[6][7]) {
    int xCount = 0;
    int oCount = 0;

    // Read the board from stdin
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            scanf(" %c", &board[i][j]); // Note the space before %c to skip whitespace

            if (board[i][j] != '-' && board[i][j] != 'X' && board[i][j]
!= 'O') {
                printf("Invalid character '%c' at row %d, column %d\n",
board[i][j], i, j);
                return false; // Invalid character found
            }
            if (board[i][j] == 'X') {
                xCount++;
            } else if (board[i][j] == 'O') {
                oCount++;
            }
        }
    }

    // Check if the difference between X and O counts is valid (0 or 1)
    if (xCount - oCount < 0 || xCount - oCount > 1) {
        printf("Invalid X and O counts. X count = %d, O count = %d\n",
xCount, oCount);
        return false;
    }

    // Check for floating pieces (pieces above empty spaces)
    for (int j = 0; j < 7; j++) {
        bool emptyFound = false;
        for (int i = 5; i >= 0; i--) { // Iterate from bottom to top
            if (board[i][j] == '-') {
                emptyFound = true;
            } else if (emptyFound && (board[i][j] == 'X' || board[i][j]
== 'O')) {
                printf("Floating piece at row %d, column %d\n", i, j);
                return false; // Floating piece found
            }
        }
    }

    return true; // Board is valid
}

int is_valid_board(char board[ROWS][COLS], FILE *input) {
    rewind(input);
    int row = 0, col = 0, c;
    int x_count = 0, o_count = 0;
    while ((c = fgetc(input)) != EOF && row < ROWS) {
        if (c == ' ' || c == '\r') continue;
        if (c == '\n') {
            if (col != COLS) {
		    printf("short row\n");
		    return 0;
	    }
            row++;
            col = 0;
            continue;
        }
        if (col >= COLS) {
		    printf("cols overflow\n");
		return 0;
	}
        if (c == '-') {
            // ok
        } else if (c == 'X') {
            x_count++;
        } else if (c == 'O') {
            o_count++;
        } else {
		printf("Invalid char: %d\n", c);
            return 0;
        }
	board[row][col] = c;
        col++;
    }

    return isValidConnect4BoardFromStdin(board);
}

void print_board(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char out = (board[i][j] == ' ' || board[i][j] == '-') ? '-' : board[i][j];
            printf("%c", out);
            if (j < COLS - 1) printf(" ");
        }
        printf("\n");
    }
}

int check_win(char board[ROWS][COLS], int row, int col, char player) {
    int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    for (int d = 0; d < 4; d++) {
        int count = 1;
        for (int dir = -1; dir <= 1; dir += 2) {
            int r = row, c = col;
            while (1) {
                r += dir * directions[d][0];
                c += dir * directions[d][1];
                if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != player)
                    break;
                count++;
            }
        }
        if (count >= 4) return 1;
    }
    return 0;
}

int apply_move(char board[ROWS][COLS], int col, char stone) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ' || board[i][col] == '-') {
            board[i][col] = stone;
            return i; // Return the row where the stone was placed
        }
    }
    return -1;
}

int is_board_full(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == ' ' || board[0][j] == '-') return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    char board[ROWS][COLS];
    int col;
    char ai_stone;
    FILE *input = stdin;
    read_board(board);
    if (!is_valid_board(board, input)) {
        printf("INVALID\n");
        return -1;
    }
    if (argc < 3) {
        printf("INVALID\n");
        return -1;
    }
    if (sscanf(argv[1], "%d", &col) != 1) {
        printf("INVALID\n");
        return -1;
    }
    ai_stone = argv[2][0];
    if (!(ai_stone == 'X' || ai_stone == 'O')) {
        printf("INVALID\n");
        return -1;
    }
    col -= 1; // Convert to 0-based index
    if (is_valid_move(board, col)) {
        int row = apply_move(board, col, ai_stone);
        if (check_win(board, row, col, ai_stone)) {
            print_board(board);
            return 1;
        } else if (is_board_full(board)) {
            printf("DRAW\n");
            print_board(board);
            return 2;
        } else {
            print_board(board);
            return 0;
        }
    } else {
        printf("INVALID\n");
        return -1;
    }
} 
