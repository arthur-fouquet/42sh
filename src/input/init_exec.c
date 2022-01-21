/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** init_exec.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "die.h"

char *verif_cmd(char *str);

void write_history_in_file(pos_t *t, char *elem)
{
    FILE *fs;

    fs = fopen("/tmp/episauce_history", "a");
    fprintf(fs, "%s\n", elem);
    t->h.history = append(t->h.history, elem);
    fclose(fs);
}

static void write_history(pos_t *t, char *elem)
{
    for (ndbl_t *temp = t->h.history->head; temp; temp = temp->next) {
        if (strcmp(temp->data, elem) == 0) {
            t->h.history->length -= 1;
            t->h.history = append(t->h.history, elem);
            return (delete_node(&t->h.history->head, temp));
        } else if (*elem == '!')
            return;
    }
    write_history_in_file(t, elem);
}

static char *init_exec_new_line(pos_t *t, char *temp)
{
    size_t len = 0;
    char *elem = NULL;

    elem = t->buffer[0];
    elem += 3;
    for (int a = 0; t->buffer[a]; len += strlen(t->buffer[a]), a++);
    temp = calloc(len - 2, sizeof(char));
    if (temp == NULL)
        die("calloc");
    temp = strcpy(temp, elem);
    for (int a = 1; t->buffer[a]; strcat(temp, t->buffer[a]), a++);
    return (temp);
}

char *init_exec(pos_t *t)
{
    char *temp = NULL;

    if (t->ind >= 1)
        temp = init_exec_new_line(t, temp);
    else {
        temp = t->buffer[0];
        temp += strlen(t->prompt);
        temp = strdup(temp);
    }
    temp = verif_cmd(temp);
    write_history(t, temp);
    t->h.first_time = true;
    t->nbr_time = 0;
    return (temp);
}
