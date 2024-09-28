* Purpose: ring buffer
 * Author: Samia Rahman 
 * Date:08th december, 2023
 * References: geeksforgeeks,tutorials point
 */

#include "ex10q1.h"
#include "stdio.h"
#include "stdlib.h"

#define INITIAL_CAPACITY 1000000 


Ring* ring_create(int capacity){
    Ring* ring_new = (Ring*)malloc(sizeof(Ring));
    if (ring_new== NULL){
        printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    ring_new -> length =0;
    ring_new -> capacity = capacity;
    ring_new -> head = (int*)malloc(sizeof(int)*capacity);
    if (ring_new->head == NULL) {
        printf("Memory not allocated. \n");
        free(ring_new);
        exit(EXIT_FAILURE);
    }
    ring_new -> start = ring_new -> head;
    ring_new ->end = ring_new -> head;
    
    return ring_new;
  
    
}

void ring_resize(Ring* ring, int new_capacity) {
    ring->head = (int*)realloc(ring->head, sizeof(int) * new_capacity);
    if (ring->head == NULL) {
        printf("Memory not allocated.\n");
        exit(EXIT_FAILURE);
    }

    // Update start and end pointers
    ring->start = ring->head;
    ring->end = ring->head + ring->length;

    // Update capacity
    ring->capacity = new_capacity;
}


void ring_push_back(Ring* ring, int value) {
    if (ring->length == ring->capacity) {
        int new_capacity = ring->capacity * 2;  
        ring_resize(ring, new_capacity);
        printf("Ring is full. Cannot push back.\n");
    }

    *(ring->end) = value;
    ring->end++;
    ring->length++;

    if (ring->end <= ring->head + ring->capacity) {
        ring->end = ring->head;
    }
}
void ring_push_front(Ring* ring, int value) {
    if (ring->length == ring->capacity) {
        int new_capacity = ring->capacity * 2;  
        ring_resize(ring, new_capacity);
        printf("Ring is full. Cannot push front.\n");
    }

    ring->start--;
    // Use pointer arithmetic to access the element
    *(ring->start) = value;
    ring->length++;
    if (ring->start < ring->head) {
        ring->start = ring->head + ring->capacity - 1;
    }

    
}


int ring_pop_front(Ring* ring, int *pop_front) {
    if (ring->length > 0) {
        // Use pointer arithmetic to access the element
        *pop_front = *(ring->start);
        ring->start = (ring->start + 1 - ring->head) % ring->capacity + ring->head;
        ring->length--;
        return 1;  // Return 1 to indicate success
    } else {
        printf("Ring is empty. Cannot pop front.\n");
        return 0;  // Return 0 to indicate failure
    }
}

int ring_pop_back(Ring* ring, int *pop_back) {
    if (ring->length > 0) {
        // Calculate the index of the element to be popped
        int popped_index = (ring->end - 1 - ring->head + ring->capacity) % ring->capacity;
        
        // Use pointer arithmetic to access the element
        *pop_back = ring->head[popped_index];
        
        // Update the end pointer
        ring->end = ring->head + popped_index;
        
        ring->length--;
        return 1;  // Return 1 to indicate success
    } else {
        printf("Ring is empty. Cannot pop back.\n");
        return 0;  // Return 0 to indicate failure
    }
}



void balanced_ring(Ring* back, Ring* front) {

    int back_total = back->length; // current back half
    int front_total = front->length; // current front half
    int all_elements = back_total + front_total;

    int target_back_half = all_elements / 2; // target back half
    int target_front_half = all_elements - target_back_half; // target front half

    if ((back_total == target_back_half && front_total == target_front_half) || (front_total == target_back_half + 1)) {
        return;
    } else if ((back_total != front_total) || (front_total != target_back_half + 1)){
        // Move elements from back to front until they're balanced
        while (front_total < target_front_half) {
            int value;
            ring_pop_back(back, &value);
            ring_push_front(front, value);
        }

        // Move elements from front to back until they're balanced
        while (front_total > target_back_half + 1) {
            int value;
            ring_pop_front(front, &value);
            ring_push_back(back, value);  
        }
    }
}
void move(Ring* ring1, Ring* ring2) {
    int pop_front_value;
    ring_pop_front(ring1, &pop_front_value);  
    ring_push_back(ring2, pop_front_value);
}






int main() {
    char command;
    int value, limit;
    Ring* front;
    Ring* back;

    // Initialize front and back RingBuffers with a certain capacity
    front = ring_create(INITIAL_CAPACITY);
    back = ring_create(INITIAL_CAPACITY);

    while ((command = getchar()) != '\n' && command != EOF) {
        switch (command) {
            case 'L':
                // Handle the 'L' command
                {
                    int pop_back;
                    ring_pop_back(back, &pop_back);
                    if (pop_back != 0) {
                        printf("%d\n", pop_back);
                    } else {
                        printf("empty\n");
                    }
                }
                break;
            case 'F':
                // Handle the 'F' command
                {
                    int pop_front;
                    ring_pop_front(front, &pop_front);
                    if (pop_front != 0) {
                        printf("%d\n", pop_front);
                    } else {
                        printf("empty\n");
                    }
                }
                break;
            case 'N':
                // Handle the 'N' command
                scanf("%d %d", &limit, &value);
                {
                    // Implementing the logic to add a non-CMPUT 201 student to the line
                    if (front->length + back->length < limit) {
                        ring_push_back(back, value);
                    }
                }
                break;
            case 'C':
                scanf(" %d %d", &limit, &value);
                if (front->length == back->length && front->length < limit) {
                    ring_push_back(front, value);
                } else if (front->length > back->length && front->length < limit) {
                    ring_push_front(back, value);
                }
                break;

            default:
                // Handle unknown command
                printf("Unknown command: %c\n", command);
                break;
        }

        // Check if balancing is needed and perform it if necessary
        while (front->length > back->length+1) {
            balanced_ring(front,back);
            move(front,back);
            
        }
        
        
        balanced_ring(front,back);
        move(front,back);
    }


    // Cleanup and free memory if needed
    free(front->head);
    free(front);
    free(back->head);
    free(back);

    return 0;
}

