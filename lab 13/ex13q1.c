/* Purpose: Practice making Makefile,Practice file I/O and command line arguments
 * Author: Samia Rahman 
 * Date:8th december, 2023
 * References: geeksforgeeks,tutorials point, scaler.com, cp-algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex13q1.h"
#define MAX_STUDENTS 2000000

int parent[MAX_STUDENTS];

// Function to initialize sets for each student
void make_array_set(int total_students) {
    for (int i = 0; i < total_students; i++) {
        parent[i] = i;
    }
}

// Function to find the set (representative) of a student
int find_Set(int studentID) {
    if (parent[studentID] == studentID) {
        return parent[studentID];
    } else if (parent[studentID] != studentID) {
        return parent[studentID] = find_Set(parent[studentID]);
    }
    return studentID;
}



// Function to perform union of two sets
void union_set(int studentID_1, int studentID_2){
    studentID_1 = find_Set(studentID_1);
    studentID_2 = find_Set(studentID_2);

    if(studentID_1==studentID_2){
        return;
    }else {
        parent[studentID_1] = studentID_2;
    }

}


int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc < 4) {
        fprintf(stderr, "Usage: %s n k f\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse command-line arguments
    int k = atoi(argv[2]);

    if (k > MAX_STUDENTS) {
        fprintf(stderr, "Student limit exceeded.\n");
        return EXIT_FAILURE;
    }
    const char *filePath = argv[3];

    // Open the input file
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Initialize sets for each student
    make_array_set(k);

    
    char work;
    int studentID_1, studentid_2;
