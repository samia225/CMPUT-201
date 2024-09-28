/* Purpose: program organization into functions,basic dynamic storage allocation and clearing,dealing with character-by-character input
 * Author: Samia Rahman 
 * Date:29th october
 * References:
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 25000

// Function to print the products in a specific aisle
void aislename(char **aisles, int aisleValue) {
    char *products = aisles[aisleValue];
    if (products == NULL) {
    } else {
        printf("%s", products); 
    }
}

int main() {
    int aislen_num;
    int position;
    int aisle_i;
    char product[MAX_LEN];

    scanf("%d", &aislen_num);

    // Initialize an array of pointers for aisles
    char **aisles = (char **)malloc(aislen_num * sizeof(char *));
    if (aisles == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < aislen_num; i++) {
        aisles[i] = NULL;  // Initialize aisles as empty
    }


    while (scanf("%d", &position) != EOF) {
        if (position == 0) {
            // Print request
            scanf("%d", &aisle_i);
            aislename(aisles, aisle_i);
            printf("\n"); // Add this line to print a newline after aisle content
            
        } else {
            // New product
            scanf("%s", product);
            aisle_i = position % aislen_num;

            // Calculate the length of the aisle and product name
            int length = 0;
            if (aisles[aisle_i] != NULL) {
                while (aisles[aisle_i][length] != '\0') {
                    length++;
                }
            }

            int proud_val = 0;
            while (product[proud_val] != '\0') {
                proud_val++;
            }

            // Allocate memory for the aisle and product
            aisles[aisle_i] = (char *)realloc(aisles[aisle_i], length + proud_val + 1);
            if (aisles[aisle_i] == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }

            // Append the product name to the aisle manually
            char *destination = aisles[aisle_i] + length;
            for (int i = 0; i < proud_val; i++) {
                *destination = product[i];
                destination++;
            }

            *destination = '\0';
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < aislen_num; i++) {
        free(aisles[i]);
    }
    free(aisles);

    return 0;
}
