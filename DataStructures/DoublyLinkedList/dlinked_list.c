#include "dlinked_list.h"

#include "stdio.h"

#include "../mem_debugger.h"

DLinkedList* dllist_create()
{
    DLinkedList* llist = malloc(sizeof(DLinkedList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return llist;
}

void dllist_push_back(DLinkedList* llist, short elem)
{
    DLinkedListNode* node = malloc(sizeof(DLinkedListNode));
    node->data = elem;
    node->ptr_next = NULL;
    node->ptr_prev = NULL;

    if (!llist->size)
    {
        llist->head = node;
        llist->tail = node;
    }

    else
    {
        DLinkedListNode* prev_tail = llist->tail;
        llist->tail = node;
        prev_tail->ptr_next = node;
        node->ptr_prev = prev_tail;
    }

    llist->size++;
}

void dllist_push_front(DLinkedList* llist, short elem)
{
    DLinkedListNode* node = malloc(sizeof(DLinkedListNode));
    node->data = elem;
    node->ptr_next = NULL;
    node->ptr_prev = NULL;

    if (!llist->size)
    {
        llist->head = node;
        llist->tail = node;
    }

    else
    {
        DLinkedListNode* prev_head = llist->head;
        llist->head = node;
        llist->head->ptr_next = prev_head;
        prev_head->ptr_prev = node;
    }

    llist->size++;
}

short dllist_pop_front(DLinkedList* llist)
{
    if (llist->size == 0) return 0;

    if (llist->size == 1)
    {
        short elem = llist->head->data;
        free(llist->head);
        llist->head = NULL;
        llist->tail = NULL;
        llist->size = 0;
        return elem;
    }

    // size > 1
    short elem = llist->head->data;
    DLinkedListNode* prev_head = llist->head;
    llist->head = llist->head->ptr_next;
    llist->head->ptr_prev = NULL;
    llist->size--;
    free(prev_head);
    return elem;
}

short dllist_pop_back(DLinkedList* llist)
{
    if (llist->size == 0) return 0;

    if (llist->size == 1)
    {
        short elem = llist->tail->data;
        free(llist->tail);
        llist->head = NULL;
        llist->tail = NULL;
        llist->size = 0;
        return elem;
    }

    // size > 1
    short elem = llist->tail->data;
    DLinkedListNode* prev_tail = llist->tail;
    llist->tail = llist->tail->ptr_prev;
    llist->tail->ptr_next = NULL;
    llist->size--;
    free(prev_tail);
    return elem;
}

int dllist_remove(DLinkedList* llist, short elem)
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
            DLinkedListNode* prev_head = llist->head;
            llist->head = llist->head->ptr_next;
            llist->head->ptr_prev = NULL;
            llist->size--;
            free(prev_head);
            return 1;
        }

        // if data is in tail
        if (llist->tail->data == elem)
        {
            DLinkedListNode* prev_tail = llist->tail;
            llist->tail = llist->tail->ptr_prev;
            llist->tail->ptr_next = NULL;
            llist->size--;
            free(prev_tail);
            return 1;
        }

        // elem should be in curr_node
        DLinkedListNode* curr_node = llist->head;
        while (curr_node && curr_node->data != elem)
            curr_node = curr_node->ptr_next;

        // no such element is list?
        if (!curr_node) return 0;

        curr_node->ptr_prev->ptr_next = curr_node->ptr_next;
        curr_node->ptr_next->ptr_prev = curr_node->ptr_prev;
        free(curr_node);

        llist->size--;
        return 1;
    }
}

int dllist_contains(DLinkedList* llist, short elem)
{
    if (llist->size == 0) return 0;

    if (llist->head->data == elem || llist->tail->data == elem)
        return 1;

    DLinkedListNode* curr_node = llist->head;
    while (curr_node && curr_node->data != elem)
        curr_node = curr_node->ptr_next;

    return curr_node ? 1 : 0;
}

short dllist_get(DLinkedList* llist, size_t index)
{
    if (index + 1 >= llist->size)
        return 0;

    else if (index == 0)
        return llist->head->data;

    else if (index == llist->size - 1)
        return llist->tail->data;

    DLinkedListNode* curr_node;

    // index is in the first half of list
    if (index <= llist->size / 2)
    {
        curr_node = llist->head;
        while (index--)
            curr_node = curr_node->ptr_next;
    }

    // index is in the second part of list
    else
    {
        index = llist->size - 1 - index;
        curr_node = llist->tail;
        while (index--)
            curr_node = curr_node->ptr_prev;
    }

    return curr_node->data;
}

short dllist_front(DLinkedList* llist)
{
    if (!llist->size) return 0;
    return llist->head->data;
}

short dllist_back(DLinkedList* llist)
{
    if (!llist->size) return 0;
    return llist->tail->data;
}

void dllist_print(DLinkedList* llist)
{
    DLinkedListNode* curr_node = llist->head;

    while (curr_node)
    {
        printf("%d ", curr_node->data);
        curr_node = curr_node->ptr_next;
    }
    printf("\n");
}

void dllist_delete(DLinkedList* llist)
{
    DLinkedListNode* curr_node = llist->head;

    while (curr_node)
    {
        DLinkedListNode* next_node = curr_node->ptr_next;
        free(curr_node);
        curr_node = next_node;
    }

    free(llist);
}
