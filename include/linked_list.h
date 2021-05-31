#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    int x;
    int fx;
} Node;

Node* data_start;

void add_node(int, int);
void free_list();

#endif