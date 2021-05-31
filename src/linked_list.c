#include "../include/linked_list.h"

void add_node(int x, int y) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->x = x;
    new_node->fx = y;

    if (data_start != NULL) {
        Node* temp = data_start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    } else {
        data_start = new_node;
    }
}

void free_list() {
    Node* temp;
    while (data_start != NULL) {
        temp = data_start;
        data_start = data_start->next;
        free(temp);
    }
}