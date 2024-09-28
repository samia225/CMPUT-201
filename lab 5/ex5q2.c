/* Purpose: Solving magic square
 * Author: Samia Rahman 
 * Date:17th october
 * References:
 */
#include "lab05.h"

// Function to check if a given grid is a magic square
int check(int n, int grid[n][n]) {
    int total = n * (n * n + 1) / 2;
    int diagonal_1 = 0;
    int diagonal_2 = 0;

    // Check rows and columns
    for (int i = 0; i < n; i++) {
        int row_sum = 0, col_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += grid[i][j];
            col_sum += grid[j][i];
        }

        if (row_sum != total) {
            return 0;
        }

        if (col_sum != total) {
            return 0; 
        }
    }

    // Check main diagonal left to right and secondary right to left

    for (int i = 0; i < n; i++) {
    diagonal_1 += grid[i][i];
    diagonal_2 += grid[i][n - 1 - i];
    }

    if (diagonal_1 != total) {
        return 0; 
    }


    if (diagonal_2 != total) {
        return 0; 
    }

    return 1; // It's a magic square
}


int magic(int n, int grid[n][n]) {
    int row = -1, col = -1;

    // Find an empty cell
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
            }
        }
        if (row != -1) {
            int result = check(n, grid);
            if (result) {
                return 1; 
            }
        }
    }


    if (row == -1) {
        return check(n, grid);
    }

    // Try to fill the empty cell 
    for (int num = 1; num <= n * n; num++) {
        int is_valid = 1;

        // Check if num is not used in the current row or column
        int no_space = 0; 

        for (int i = 0; i < n && !no_space; i++) {
            if (grid[row][i] == num) {
                is_valid = 0;
            }
            if (grid[i][col] == num) {
                is_valid = 0;
            }

            if (grid[row][i] == num && grid[i][col] == num) {
                no_space = 1; 
            }
        }

        if (is_valid && !no_space) {
            grid[row][col] = num;

            // Recur to fill the next cell
            if (magic(n, grid)) {
                return 1;
            }

            // backtrack
            grid[row][col] = 0;
        }
    }

    return 0; 
}

// Do not touch anything in this main function (used for testing purposes)
int main() {
    return test_magic(magic);  // This line runs a compiled function in lab05b.o
}
