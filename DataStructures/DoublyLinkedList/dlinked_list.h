#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "stdlib.h"

typedef struct DLinkedListNode
{
    short data;
    struct DLinkedListNode* ptr_next;
    struct DLinkedListNode* ptr_prev;
}
DLinkedListNode;

typedef struct
{
    DLinkedListNode *head, *tail;
    size_t size;
}
DLinkedList;

DLinkedList* dllist_create();

void dllist_push_back(DLinkedList* llist, short elem);
void dllist_push_front(DLinkedList* llist, short elem);

short dllist_pop_front(DLinkedList* llist);
short dllist_pop_back(DLinkedList* llist);
int dllist_remove(DLinkedList* llist, short elem);

int dllist_contains(DLinkedList* llist, short elem);
short dllist_get(DLinkedList* llist, size_t index);

short dllist_front(DLinkedList* llist);
short dllist_back(DLinkedList* llist);

void dllist_print(DLinkedList* llist);

void dllist_delete(DLinkedList* llist);

#endif
