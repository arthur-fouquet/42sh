/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** delete_node.c
*/

#include <stdlib.h>
#include "linked_list.h"

void delete_node(ndbl_t **head_ref, ndbl_t *del)
{
    if (*head_ref == NULL || del == NULL)
        return;
    if (*head_ref == del)
        *head_ref = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;
    free(del->data);
    free(del->date);
    free(del);
}
