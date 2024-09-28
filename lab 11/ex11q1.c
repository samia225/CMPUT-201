/* Purpose: structs, linked lists
 * Author: Samia Rahman 
 * Date:26th november, 2023
 * References: geeksforgeeks,tutorials point
 */

#include "ex11q1.h"
#include "stdio.h"
#include "stdlib.h"
// ############################################################################
// Vector
// ############################################################################

Vec* vec_create(void){
    Vec* vector_new = (Vec*)malloc(sizeof(Vec));
    if (vector_new== NULL){
        printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    vector_new -> length = 0;
    vector_new -> capacity = 10;
    vector_new -> storage = (int*)malloc(sizeof(int)*vector_new->capacity);
    if (vector_new -> storage == NULL) {
        printf("Memory not allocated. \n");
        free(vector_new);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vector_new->capacity; i++) {
        vector_new->storage[i] = 0;  // set the default value here
    }

    return vector_new;

}

void vec_insert_at(Vec* vec, int at, int item){
    if (vec -> length == vec -> capacity) {
        vec -> capacity *= 2;
        vec -> storage = (int*)realloc(vec ->storage, vec-> capacity * sizeof(int));
        if (vec -> storage == NULL) {
            printf("Memory not allocated. \n");
            exit(EXIT_FAILURE);
        }
    }

    if (at<0 || at > vec -> length){
        printf("Invalid index");
        exit(EXIT_FAILURE);
    }

    for (int i = vec->length; i > at; i--) {
        vec->storage[i] = vec->storage[i - 1];
    }

    vec -> storage[at] = item;
    vec -> length ++;
}

void vec_print(Vec* vec) {
    printf("[");
    for (int i = 0; i < vec->length; i++) {
        printf("%d", vec->storage[i]);
        if (i < vec->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


void vec_free(Vec* vec) {
    free(vec->storage);
    free(vec);
}



// ############################################################################
// Linked List
// ############################################################################

LinkedListNode* list_node_create(int item){
    LinkedListNode* first = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (first == NULL) {
        printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    first -> item = item;
    first -> next = NULL;

    return first;

}




LinkedList* list_create(void){
    LinkedList* new_list = (LinkedList*)malloc(sizeof(LinkedList));
    if (new_list ==NULL){
    printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    new_list ->length = 0;
    new_list -> start = NULL;

    return new_list;

}

void list_insert_at(LinkedList* list, int at, int item) {
    if (at < 0 || at > list->length) {
        printf("Invalid index\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode* new_node = list_node_create(item);

    if (at == 0) {
        new_node->next = list->start;
        list->start = new_node;
    } else {
        LinkedListNode* present_node = list->start;
        for (int i = 0; i < at - 1; i++) {
            present_node = present_node->next;
        }

        new_node->next = present_node->next;
        present_node->next = new_node;
    }

    if (list->length == 0 || at == 0) {
        // Update list->start only if the list was initially empty or we inserted at position 0
        list->start = new_node;
    }

    list->length++;
}


void list_print(LinkedList* list) {
    printf("[");
    LinkedListNode* current_node = list->start;

    while (current_node != NULL) {
        printf("%d", current_node->item);
        current_node = current_node->next;

        if (current_node != NULL) {
            printf(", ");
        }
    }

    printf("]\n");
}



void list_free(LinkedList* list){
    LinkedListNode* current_node = list->start;
    LinkedListNode* next;

    while (current_node != NULL) {
        next = current_node->next;
        free(current_node);
        current_node = next;
    }

    free(list);
}

// ############################################################################
// Doubly Linked List
// ############################################################################

DoublyLinkedListNode* dlist_node_create(int item){
    DoublyLinkedListNode* first_node = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    if (first_node == NULL) {
        printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    first_node -> item = item;
    first_node -> prev = NULL;
    first_node -> next = NULL;

    return first_node;

}



DoublyLinkedList* dlist_create(void){
    DoublyLinkedList* dnew_list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (dnew_list ==NULL){
    printf("Memory not allocated. \n");
        exit(EXIT_FAILURE);
    }

    dnew_list ->length = 0;
    dnew_list -> start = NULL;
    dnew_list -> end = NULL;


    return dnew_list;

}

void dlist_insert_at(DoublyLinkedList* l, int at, int item) {
    if (at < 0 || at > l->length) {
        printf("Invalid index\n");
        exit(EXIT_FAILURE);
    }

    DoublyLinkedListNode* main_node = dlist_node_create(item);

    if (at == 0) {
        // If inserting at the beginning
        if (l->length == 0) {
            // If the list is empty, update both start and end
            l->start = main_node;
            l->end = main_node;
        } else {
            // If the list is not empty, insert at the beginning
            main_node->next = l->start;
            main_node->prev = NULL;
            l->start->prev = main_node; // Update the prev pointer of the existing first node
            l->start = main_node; // Update the start pointer to the new node
        }
    } else if (at == l->length) {
        // If inserting at the end
        main_node->prev = l->end;
        main_node->next = NULL;
        l->end->next = main_node; // Update the next pointer of the existing last node
        l->end = main_node; // Update the end pointer to the new node
    } else {
        // If inserting in the middle
        DoublyLinkedListNode* present_node;
        // Start traversal from the end if it's closer
        if (at >= l->length / 2) {
            present_node = l->end;
            for (int i = l->length - 1; i > at; i--) {
                present_node = present_node->prev;
            }
        } else {
            // Otherwise, start traversal from the beginning
            present_node = l->start;
            for (int i = 0; i < at; i++) {
                present_node = present_node->next;
            }
        }

        main_node->next = present_node;
        main_node->prev = present_node->prev;

        if (present_node->prev != NULL) {
            present_node->prev->next = main_node;
        } else {
            // If we're inserting at the beginning, update start
            l->start = main_node;
        }

        present_node->prev = main_node;
    }

    l->length++;
}



void dlist_print(DoublyLinkedList* l) {
    printf("[");
    DoublyLinkedListNode* present = l->start;

    while (present != NULL) {
        printf("%d", present->item);

        if (present->next != NULL) {
            printf(", ");
        }

        present = present->next;
    }

    printf("]\n");
}

void dlist_free(DoublyLinkedList* l){
    DoublyLinkedListNode* present = l->start;
    DoublyLinkedListNode* next;

    while (present != NULL) {
        next = present->next;
        free(present);
        present = next;
    }

    free(l);
}


// ############################################################################
// Main
// ############################################################################
int main(void) {
    char line[1000];
    // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
       int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            vec_insert_at(v, b, a);
        } else {
            scanf("%s\n", line);
            vec_print(v);
        }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    LinkedList* l = list_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            list_insert_at(l, b, a);
        } else {
            scanf("%s\n", line);
            list_print(l);
        }
    }

    list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    DoublyLinkedList* dlist = dlist_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            dlist_insert_at(dlist, b, a);
        } else {
            scanf("%s\n", line);
            dlist_print(dlist);
       }
    }

    dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}
