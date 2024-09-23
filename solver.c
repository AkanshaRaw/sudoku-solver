#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

// Function to print the board
void printBoard(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%2d", board[row][col]);
        }
        printf("\n");
    }
}

// Function to check if it's valid to place num at board[row][col]
bool isValid(int board[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }
    
    // Check column
    for (int x = 0; x < SIZE; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell
bool findEmptyLocation(int board[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (board[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Main solver function using backtracking
bool solveSudoku(int board[SIZE][SIZE]) {
    int row, col;

    // If no empty space is left, the puzzle is solved
    if (!findEmptyLocation(board, &row, &col)) {
        return true;
    }

    // Try numbers 1 through 9 in the empty spot
    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;

            // Recursively try filling the next cell
            if (solveSudoku(board)) {
                return true;
            }

            // If the number doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    return false; // Triggers backtracking
}

int main() {
    // Input Sudoku grid (0 represents an empty cell)
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        printBoard(board);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
