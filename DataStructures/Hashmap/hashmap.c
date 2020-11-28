#include "hashmap.h"

#include "stdio.h"
#include "stdint.h"

// linked list =====================================

LinkedList* llist_create()
{
    LinkedList* llist = malloc(sizeof(LinkedList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return llist;
}

void llist_push_front(LinkedList* llist, short elem)
{
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->data = elem;
    node->ptr_next = NULL;

    if (!llist->size)
    {
        llist->head = node;
        llist->tail = node;
    }

    else
    {
        LinkedListNode* prev_head = llist->head;
        llist->head = node;
        llist->head->ptr_next = prev_head;
    }

    llist->size++;
}

int llist_remove(LinkedList* llist, short elem)
{
    if (!llist->size) return 0;

    if (llist->size == 1)
    {
        if (llist->head->data != elem)
            return 0;

        free(llist->head);
        llist->head = NULL;
        llist->tail = NULL;
        llist->size = 0;
        return 1;
    }

    // size > 1
    else
    {
        // if data is in head
        if (llist->head->data == elem)
        {
            LinkedListNode* prev_head = llist->head;
            llist->head = llist->head->ptr_next;
            llist->size--;
            free(prev_head);
            return 1;
        }

        // elem should be in curr_node->ptr_next
        LinkedListNode* curr_node = llist->head;
        while (curr_node->ptr_next && curr_node->ptr_next->data != elem)
            curr_node = curr_node->ptr_next;

        // no such element is list?
        if (!curr_node->ptr_next) return 0;

        // if data is in tail
        if (curr_node->ptr_next == llist->tail)
        {
            LinkedListNode* prev_tail = llist->tail;
            llist->tail = curr_node;
            llist->tail->ptr_next = NULL;
            free(prev_tail);
        }

        // data is not in tail
        else
        {
            LinkedListNode* node_to_del = curr_node->ptr_next;
            curr_node->ptr_next = curr_node->ptr_next->ptr_next;
            free(node_to_del);
        }

        llist->size--;
        return 1;
    }
}

int llist_contains(LinkedList* llist, short elem)
{
    if (llist->size == 0) return 0;

    if (llist->head->data == elem || llist->tail->data == elem)
        return 1;

    LinkedListNode* curr_node = llist->head;
    while (curr_node && curr_node->data != elem)
        curr_node = curr_node->ptr_next;

    return curr_node ? 1 : 0;
}

void llist_print(LinkedList* llist)
{
    LinkedListNode* curr_node = llist->head;

    while (curr_node)
    {
        printf("%d ", curr_node->data);
        curr_node = curr_node->ptr_next;
    }
    printf("\n");
}

void llist_delete(LinkedList* llist)
{
    LinkedListNode* curr_node = llist->head;

    while (curr_node)
    {
        LinkedListNode* next_node = curr_node->ptr_next;
        free(curr_node);
        curr_node = next_node;
    }

    free(llist);
}

// linked list end =====================================

HashMap* hashmap_create(size_t array_size)
{
    HashMap* map = malloc(array_size * sizeof(HashMap));

    map->array = malloc(array_size * sizeof(LinkedList*));
    for (int i = 0; i < array_size; i++)
        map->array[i] = llist_create();
    
    map->array_size = array_size;
    map->size = 0;
    
    return map;
}

static uint32_t hash_func(short elem)
{
    uint32_t key = elem;
    
    key = ~key + (key << 15); 
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057; 
    key = key ^ (key >> 16);

    return key;
}

void hashmap_insert(HashMap* map, short elem)
{
    uint32_t index = hash_func(elem) % map->array_size;
    llist_push_front(map->array[index], elem);
    map->size++;
}

int hashmap_remove(HashMap* map, short elem)
{
    uint32_t index = hash_func(elem) % map->array_size;
    if (llist_remove(map->array[index], elem))
    {
        map->size--;
        return 1;
    }
    return 0;
}

int hashmap_contains(HashMap* map, short elem)
{
    uint32_t index = hash_func(elem) % map->array_size;
    return llist_contains(map->array[index], elem);
}

void hashmap_print(HashMap* map)
{
    for (int i = 0; i < map->array_size; i++)
    {
        if (map->array[i]->size)
        {
            printf("%.3d: ", i);
            llist_print(map->array[i]);
        }
    }
    printf("\n");
}