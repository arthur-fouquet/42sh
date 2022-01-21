/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** linked_list.c
*/

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"
#include "die.h"

char *get_time(void);

dblist_t *load_from_file(dblist_t *list)
{
    char *str = NULL;
    size_t sz = 0;
    FILE *fs = fopen("/tmp/episauce_history", "r");

    while (getline(&str, &sz, fs) != -1) {
        str[strlen(str)-1] = '\0';
        append(list, str);
    }
    free(str);
    fclose(fs);
    return (list);
}

dblist_t *new_double_list(void)
{
    bool create = false;
    struct stat fs_stat;
    dblist_t *new_node = calloc(1, sizeof(dblist_t));

    if (new_node == NULL)
        die("calloc");
    if (lstat("/tmp/episauce_history", &fs_stat) == -1)
        create = true;
    new_node->length = 0;
    new_node->head = NULL;
    new_node->tail = NULL;
    if (create == false && fs_stat.st_size != 0)
        return (load_from_file(new_node));
    if (fopen("/tmp/episauce_history", "w") == NULL)
        die("fopen");
    return (new_node);
}

dblist_t *append(dblist_t *list, char *data)
{
    ndbl_t *new_node;

    if (list == NULL)
        return (list);
    new_node = calloc(1, sizeof(ndbl_t));
    if (new_node == NULL)
        die("calloc");
    new_node->data = strdup(data);
    new_node->date = get_time();
    new_node->next = NULL;
    if (list->tail == NULL) {
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->length++;
    return (list);
}

void list_delete(dblist_t **p_list)
{
    ndbl_t *elem;
    ndbl_t *temp;

    if (*p_list == NULL)
        return;
    temp = (*p_list)->head;
    while (temp != NULL) {
        elem = temp;
        free(temp->data);
        free(temp->date);
        temp = temp->next;
        free(elem);
    }
    free(*p_list);
    *p_list = NULL;
}
