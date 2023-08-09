#include "sort.h"
#include <stdio.h>

void insertion_sort_list(listint_t **list)
{
    listint_t *node = malloc(sizeof(*node));
    listint_t *tmp = malloc(sizeof(*tmp));
    listint_t *head = malloc(sizeof(* head));

    node->next = head->next= tmp->next= *list;
    
    while(node->next)
    {
        if (node->n < node->prev->n)
        {
            tmp->next = node->next;
            tmp->prev = node->prev;
            node->next = head->next;
            node->prev = head->prev;
            *head = *tmp;
            print_list(*list);
        }
        node->next = node->next->next;
    }
}