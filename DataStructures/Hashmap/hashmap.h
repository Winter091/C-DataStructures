#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "stdlib.h"

// linked list =====================================

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

void llist_push_front(LinkedList* llist, short elem);
int llist_remove(LinkedList* llist, short elem);
int llist_contains(LinkedList* llist, short elem);
void llist_print(LinkedList* llist);

void llist_delete(LinkedList* llist);

// linked list end =====================================

typedef struct
{
    LinkedList** array;
    
    size_t array_size;
    size_t size;
}
HashMap;

HashMap* hashmap_create(size_t array_size);

void hashmap_insert(HashMap* map, short elem);
int hashmap_remove(HashMap* map, short elem);
int hashmap_contains(HashMap* map, short elem);
void hashmap_print(HashMap* map);

#endif

