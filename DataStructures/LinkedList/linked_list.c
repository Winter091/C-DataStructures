#include "linked_list.h"

#include "stdio.h"

LinkedList* llist_create()
{
    LinkedList* llist = malloc(sizeof(LinkedList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return llist;
}

void llist_push_back(LinkedList* llist, short elem)
{
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->data = elem;
    node->ptr_next = NULL;

    // size = 0
    if (!llist->head)
    {
        llist->head = node;
        llist->tail = node;
    }

    // size > 0
    else
    {
        LinkedListNode* prev_tail = llist->tail;
        llist->tail = node;
        prev_tail->ptr_next = node;
    }

    llist->size++;
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

short llist_pop_front(LinkedList* llist)
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
    LinkedListNode* prev_head = llist->head;
    llist->head = llist->head->ptr_next;
    llist->size--;
    free(prev_head);
    return elem;
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

short llist_get(LinkedList* llist, size_t index)
{
    if (index + 1 >= llist->size)
        return 0;

    if (index == 0)
        return llist->head->data;

    else if (index == llist->size - 1)
        return llist->tail->data;

    else
    {
        LinkedListNode* curr_node = llist->head;
        while (index--)
            curr_node = curr_node->ptr_next;

        return curr_node->data;
    }
}

short dllist_front(LinkedList* llist)
{
    if (!llist->size) return 0;
    return list->head->data;
}

short dllist_back(LinkedList* llist)
{
    if (!llist->size) return 0;
    return list->tail->data;
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
