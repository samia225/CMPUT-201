/* Purpose: program organization into functions,basic dynamic storage allocation 
 * Author: Samia Rahman 
 * Date:05th november, 2023
 * References: geeksforgeeks,
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ex8q1.h"


int main() {
    int is_print, value;
    float index;
    float* idex_2 = NULL;
    int* val = NULL;
    int size = 0;

    while (!feof(stdin)) {
        read_line(&is_print, &index, &value);

        if (is_print == 1) {
            if (size > 0) {
                printf("[");
                bool inital = true;  // Track if it's the first element
                for (int i = 0; i < size; i++) {
                    if (!inital) {
                        printf(", ");
                    }
                    inital = false;
                    printf("%d", val[i]);
                }
                printf("]\n");
            } else {
                printf("[]\n");
            }
        } else {
            // Using binary search here
            int first = 0;
            int last = size - 1;
            int position = 0;
            int present = 0;

            while (first <= last) {
                int middle = (first + last) / 2;
                if (idex_2[middle] < index) {
                    first = middle+1;
                } else if (idex_2[middle] > index) {
                    last = middle-1;
                } else {
                    val[middle] = value;
                    present = 1;
                    first = last+1;  // Exit the loop when the index is found
                }
            }

            if (!present) {
                // Find the correct position for insertion
                for (position =0; position < size && idex_2[position] < index; position++) {
                    
                }

                // Reallocate and insert the new index and value
                idex_2 = realloc(idex_2, (size + 1) * sizeof(float));
                val = realloc(val, (size + 1) * sizeof(int));

                for (int i = size; i > position; i--) {
                    idex_2[i] = idex_2[i - 1];
                    val[i] = val[i - 1];
                }

                idex_2[position] = index;
                val[position] = value;
                size++;
            }
        }
    }

    free(idex_2);
    free(val);

    return 0;
}
