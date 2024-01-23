#include <stdlib.h>
#include <stdio.h>

struct list_item {
    int value;
    struct list_item * next;
};

void append(struct list_item *first, int x) {
    struct list_item *new_item = (struct list_item*) malloc(sizeof(struct list_item));
    new_item->next = NULL;
    new_item->value = x;
    struct list_item *temp_ptr = first;
    while(temp_ptr->next != NULL) {
        temp_ptr = temp_ptr->next;
    }
    temp_ptr->next = new_item;
}

void prepend(struct list_item *first, int x) {
    struct list_item *second_item = (struct list_item*) malloc(sizeof(struct list_item));
    second_item->value = x;    
    second_item->next = first->next;
    first->next = second_item;
}

void print(struct list_item *first) {
    struct list_item *temp_ptr = first;
    while(temp_ptr != NULL) {
        printf("Value: %i\n", temp_ptr->value);
        temp_ptr = temp_ptr->next;
    }
}

void input_sorted(struct list_item *first, int x) {
    struct list_item *temp_ptr = first;
    if(first->value > x) {
        prepend(first, x);
    } else {
        while(temp_ptr->next != NULL) {
            if (temp_ptr->next->value > x){
                prepend(temp_ptr, x);
                return;
            } 
            else {
                temp_ptr = temp_ptr->next;
            }
        }
        append(temp_ptr, x);
    }
}

void clear(struct list_item *first) {
        struct list_item *temp_ptr = first->next;
        do {
            struct list_item *temp_next_ptr = temp_ptr->next;
            free(temp_ptr);
            temp_ptr = temp_next_ptr;
        } while(temp_ptr != NULL);
}

int main(int argc, char ** argv) {
    struct list_item root;
    root.value = -1;
    root.next = NULL;
    //append(&root, 21);
    prepend(&root, 69);
    prepend(&root, 40);
    append(&root,10);
    //print(&root);
    input_sorted(&root, 50);
    input_sorted(&root, 53);
    input_sorted(&root, 72);
    print(&root);
    clear(&root);
}