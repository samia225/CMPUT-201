/*Author: Samia Rahman
*Date: October 9th
*Purpose: Sorting and searching
*Persons discussed w/:
*References:
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    double weight[2000];
    scanf("%d", &n);
     // Assuming a maximum of 2000 box weights
    for (int i = 0; i < n; i++) {
        scanf("%lf", &weight[i]);
    }

     // using bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (weight[j] > weight[j + 1]) {
                double temp = weight[j];
                weight[j] = weight[j + 1];
                weight[j + 1] = temp;
            }
        }
    }

    double capacity;
    while (scanf("%lf", &capacity) != EOF) { // Read until EOF
        int max_boxes = 0;
        double weight_now = 0.0;


        for (int i = 0; i < n; i++) {
            if (weight_now + weight[i] <= capacity) {
                weight_now += weight[i];
                max_boxes++;
            }
        }

        printf("%d\n", max_boxes);
    }

    return 0;
}
