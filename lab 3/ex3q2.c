New! Keyboard shortcuts … Drive keyboard shortcuts have been updated to give you first-letters navigation
/*Author: Samia Rahman
*Date: 29st September
*Purpose: 
*Persons discussed w/:
*References:
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_values = 22; // 20 integers + x + y
    int values[num_values];
    int min;
    int max;
    
    //printf("Enter %d integers: ", num_values);

    for (int i = 0; i < num_values; i++) {
        if (scanf("%d", &values[i]) != 1) {
            // Invalid input, not an integer
            fprintf(stderr, "Invalid input. Please enter integers only.\n");
            return 1; // Terminate with non-zero exit code
        }

        // Initialize max and min with the first value
        if (i == 0) {
            max = min = values[i];
        }

        // Find max and min
        if (values[i] > max) {
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
    }

    int x = values[num_values - 2];
    int y = values[num_values - 1];
    int result = x * max + y * min;

    printf("x * max + y * min: %d\n", result);

    return 0;
}
