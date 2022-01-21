/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Queue function
*/

#include <stdlib.h>
#include <string.h>
#include "input.h"

int push(pos_t *t, queue_t data)
{
    queue_t *new_elem = calloc(1, sizeof(queue_t));

    if (new_elem == NULL)
        return (84);
    if (strlen(data.path) == 0)
        return (push(t, (queue_t) {".",
            strlen(t->buffer[t->ind]),NULL}));
    new_elem->path = strdup(data.path);
    new_elem->cursor = data.cursor;
    new_elem->next = NULL;
    if (t->dir == NULL) {
        t->dir = new_elem;
        return (0);
    }
    new_elem->next = t->dir;
    t->dir = new_elem;
    return (0);
}

void pop_queue(queue_t **queue)
{
    queue_t *old_head = *queue;

    if (old_head == NULL)
        return;
    *queue = ((*queue)->next);
    free(old_head);
}