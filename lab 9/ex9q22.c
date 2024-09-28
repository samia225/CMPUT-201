/* Purpose: SString arithmetic
 * Author: Samia Rahman 
 * Date:12th november
 * References:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1010

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void add(char *number1, char *number2) {
    int carry = 0;
    int numb1_len = strlen(number1);
    int numb2_len = strlen(number2);

    reverseString(number1);
    reverseString(number2);

    int maxLen;
    if (numb1_len > numb2_len) {
        maxLen = numb1_len;
    } else {
        maxLen = numb2_len;
    }

    for (int i = 0; i < maxLen || carry; ++i) {
        int digit1, digit2;

        if (i < numb1_len) {
            digit1 = number1[i] - '0';
        } else {
            digit1 = 0;
        }

        if (i < numb2_len) {
            digit2 = number2[i] - '0';
        } else {
            digit2 = 0;
        }

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        if (i < numb1_len) {
            number1[i] = sum % 10 + '0';
        } else {
            // If num1 is shorter than num2, append new digits to the end
            number1[numb1_len++] = sum % 10 + '0';
        }
    }
    reverseString(number1);
}

void concatenate(char *number1, char *number2) {
    strcat(number1, number2);
}

void rotateRight(char **a, int positions) {
    int len_a = strlen(*a);

    // Allocate memory for the rotated string
    char *rotatedString = (char *)malloc((len_a + 1) * sizeof(char));
    if (rotatedString == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Perform the rotations
    for (int i = 0; i < positions; i++) {
        char lastDigit = (*a)[len_a - 1];

        // Shift all digits to the right, starting from the end
        for (int j = len_a - 1; j > 0; j--) {
            rotatedString[j] = (*a)[j - 1];
        }

        // Place the last digit at the beginning
        rotatedString[0] = lastDigit;

        // Swap pointers to update the rotated string
        char *temp = *a;
        *a = rotatedString;
        rotatedString = temp;
    }

    // Remove leading zeros if the final rotated string is not "0"
    if (strcmp(*a, "0") != 0) {
        int i, j;
        int finalLen = strlen(*a);

        for (i = 0; i < finalLen; i++) {
            if ((*a)[i] != '0') {
                break;
            }
        }

        // Shift the non-zero digits to the beginning of the string
        for (j = 0; i < finalLen; i++, j++) {
            (*a)[j] = (*a)[i];
        }

        // Null-terminate the new string
        (*a)[j] = '\0';
    }

    // Free the original string's memory
    free(rotatedString);
}




int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) {
        fprintf(stderr, "Invalid input for the number of operations\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        char op[4];  // Allow space for '\0'
        char *a = (char *)malloc(MAX_DIGITS * sizeof(char));
        char b[MAX_DIGITS];

        if (a == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        if (scanf("%s %s", a, op) != 2) {
            fprintf(stderr, "Error reading operation\n");
            free(a);
            return EXIT_FAILURE;
        }

        if (strcmp(op, "+") == 0) {
            if (scanf("%s", b) != 1) {
                fprintf(stderr, "Error reading second operand for addition\n");
                free(a);
                return EXIT_FAILURE;
            }
            add(a, b);
        } else if (strcmp(op, "@") == 0) {
            if (scanf("%s", b) != 1) {
                fprintf(stderr, "Error reading second operand for concatenation\n");
                free(a);
                return EXIT_FAILURE;
            }
            concatenate(a, b);
        } else if (strcmp(op, "rot") == 0) {
            int positions;
            if (scanf("%d", &positions) != 1 || positions < 0 || positions > 1000) {
                fprintf(stderr, "Invalid input for rotation positions\n");
                free(a);
                return EXIT_FAILURE;
            }
            rotateRight(&a, positions);
        }

        printf("%s\n", a);

        // Free the dynamically allocated memory for a
        free(a);
    }

    return 0;
}
