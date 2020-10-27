#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "stdlib.h"

typedef struct LinkedListNode
{
    short data;
    struct LinkedListNode* ptr_next;
}
LinkedListNode;

typedef struct
{
    LinkedListNode *head, *tail;
    size_t size;
}
LinkedList;

LinkedList* llist_create();

void llist_push_back(LinkedList* llist, short elem);
void llist_push_front(LinkedList* llist, short elem);

int llist_pop_front(LinkedList* llist, short* elem);
int llist_remove(LinkedList* llist, short elem);

int llist_contains(LinkedList* llist, short elem);
int llist_get(LinkedList* llist, size_t index, short* elem);

void llist_print(LinkedList* llist);

void llist_delete(LinkedList* llist);

#endif
