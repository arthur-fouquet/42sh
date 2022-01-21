/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** flag_history.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

void write_history_in_file(pos_t *t, char *elem);

static char *refresh_hist(pos_t *t, ndbl_t *hist, char *elem)
{
    size_t len = strlen(hist->data) + strlen(elem) + 1;
    char *temp = calloc(len, sizeof(char));

    temp = strcpy(temp, hist->data);
    temp = strcat(temp, elem);
    dprintf(1, "%s\n", temp);
    if (elem[0] == 0) {
        t->h.history->length -= 1;
        t->h.history = append(t->h.history, hist->data);
        delete_node(&t->h.history->head, hist);
    } else
        write_history_in_file(t, temp);
    return (temp);
}

static char *flag_excla_alpha(pos_t *t, char *elem, ndbl_t *hist)
{
    int a = 0;
    char *temp = calloc(10, sizeof(char));

    for (a = 0; *elem != ' ' && *elem != '\0'; elem++, a++)
        temp[a] = *elem;
    temp[a] = '\0';
    for (; hist; hist = hist->next)
        if (strstr(hist->data, temp) != NULL)
            return (refresh_hist(t, hist, elem));
    dprintf(2, "%s: Event not found.\n", temp);
    return (NULL);
}

static char *flag_excla_num(pos_t *t, char *elem, ndbl_t *hist)
{
    bool digit = true;
    int nbr = atoi(elem);

    for (; *elem != ' ' && *elem; elem++)
        if (isdigit(*elem) == 0)
            digit = false;
    if (digit == false || nbr > t->h.history->length) {
        dprintf(2, "%s: Event not found.\n", elem);
        return (NULL);
    }
    for (int a = 1; a != nbr; a++, hist = hist->next);
    return (refresh_hist(t, hist, elem));
}

char *flag_excla(pos_t *t, char *command)
{
    char *elem = strstr(command, "!");
    ndbl_t *hist = t->h.history->head;

    if (isdigit(*++elem) != 0) {
        return (flag_excla_num(t, elem, hist));
    } else if (isalpha(*elem))
        return (flag_excla_alpha(t, elem, hist));
    return (NULL);
}
