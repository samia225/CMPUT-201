/* Purpose: Sorting
 * Author: Samia Rahman 
 * Date:25th october
 * References: geeksforgeeks
 */
#include <stdio.h>
#include "ex6q2.h"

// Please don't change anything in this main function!
int main(void) {
    if (!test_bubble(bubble_sort))
        fprintf(stderr, "Bubble sorting failed\n");
    if (!test_gnome(gnome_sort))
        fprintf(stderr, "Gnome sorting failed\n");
    if (!test_insertion(insertion_sort))
        fprintf(stderr, "Insertion sorting failed\n");
    if (!test_custom(custom_sort)) {
        fprintf(stderr, "Custom sorting failed\n");
	}
	return 0;
}




// Implementation of Bubble Sort
void bubble_sort(int n, int arr[n]) {
    int swapp = 1;
    for (int i = 0; i < n - 1 && swapp; i++) {
        swapp = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapp = 1;
            }
        }
    }
}


// Implementation of Gnome Sort
void gnome_sort(int n, int arr[n]) {
    int p = 1;
    while (p < n) {
        if (arr[p] >= arr[p - 1]) {
            p++;
        } else {
            int temp = arr[p];
                arr[p] = arr[p - 1];
                arr[p - 1] = temp;
            if (p > 1) {
                p--;
            }
        }
    }
}

// Implementation of Insertion Sort
void insertion_sort(int n, int arr[n]) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j;

        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

// Implementation of Comb Sort
void custom_sort(int n, int arr[n]) {
    int f = n; // Initialize f
    int swapped = 1; // Flag to check if a swap occurred

    do {
        // Calculate the f using a shrink factor
        f = (f * 10) / 13;
        if (f < 1) {
            f = 1;
        }

        swapped = 0; // Reset the swap flag

        // Compare and swap elements with the calculated f
        for (int i = 0; i < n - f; i++) {
            if (arr[i] > arr[i + f]) {
                int temp = arr[i];
                arr[i] = arr[i+f];
                arr[i+f] = temp;
                swapped = 1;
            }
        }
    } while (f > 1 || swapped);
}
