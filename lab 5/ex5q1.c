/* Purpose: Sudoku validator
 * Author: Samia Rahman 
 * Date:17th october
 * References:
 */

#include <stdio.h>
int isValidSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        // Arrays to track seen numbers in rows, columns, and 3x3 sub-grids
        int row1[9] = {0};
        int col1[9] = {0};
        int subgrid_count[9] = {0};

        for (int j = 0; j < 9; j++) {
            // Check rows and columns
            int r_num = board[i][j] - 1;
            int c_num = board[j][i] - 1;

            if (row1[r_num] == 1 || col1[c_num] == 1) {
                return 0;
            }

            row1[r_num] = 1;
            col1[c_num] = 1;

            // Check 3x3 sub-grids
            int sub_r = 3 * (i / 3) + j / 3;
            int sub_c = 3 * (i % 3) + j % 3;
            int num = board[sub_r][sub_c] - 1;

            if (subgrid_count[num] == 1) {
                return 0;
            }

            subgrid_count[num] = 1;
        }
    }

    return 1;  // Valid Sudoku
}

int main() {
    int board[9][9];


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(stdin, "%1d", &board[i][j]); 
            }
        }
    


    // Check if the Sudoku board is valid
    if (isValidSudoku(board)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}
