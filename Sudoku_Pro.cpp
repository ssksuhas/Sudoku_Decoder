#include <iostream>
using namespace std;

#define N 9  // Size of the Sudoku grid

// Function to check if placing num at grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check the row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we reach the end of the row, move to the next row
    if (col == N) {
        row++;
        col = 0;
    }

    // If we reach the end of the board, the Sudoku is solved
    if (row == N) return true;

    // Skip pre-filled cells
    if (grid[row][col] != 0) return solveSudoku(grid, row, col + 1);

    // Try placing numbers 1-9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;  // Place number
            if (solveSudoku(grid, row, col + 1)) return true;
            grid[row][col] = 0;  // Backtrack if not valid
        }
    }

    return false;  // No valid number found
}

// Function to print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Driver function
int main() {
    int grid[N][N] = {
        {0, 2, 0, 0, 0, 0, 0, 9, 4},  
        {0, 0, 0, 2, 0, 0, 0, 0, 0},  
        {7, 0, 0, 0, 0, 3, 6, 0, 0},  
        {0, 0, 5, 0, 0, 8, 0, 0, 0},  
        {0, 0, 0, 0, 0, 0, 0, 0, 0},  
        {0, 0, 0, 5, 0, 0, 9, 0, 0},  
        {0, 0, 7, 6, 0, 0, 0, 0, 1},  
        {0, 0, 0, 0, 0, 7, 0, 0, 0},  
        {3, 4, 0, 0, 0, 0, 0, 7, 0} 
    };

    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists!";
    }

    return 0;
}
