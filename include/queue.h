/*
** EPITECH PROJECT, 2020
** CPE_lemin_2019
** File description:
** Queue header
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// # Structure
typedef struct queue_s queue_t;

struct queue_s {
    char *path;
    size_t cursor;
    queue_t *next;
};


// # Functions
void pop_queue(queue_t **queue);
#endif // QUEUE_H