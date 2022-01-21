/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** builtin_input.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "parameters.h"
#include "definition.h"

char *flag_excla(pos_t *t, char *command);

void builtin_history(UNUSED char **tab , head_t *head)
{
    int i = 1;

    for (ndbl_t *temp = head->hist->h.history->head;
        temp; temp = temp->next, i++) {
        for (int a = 0; a != 6 - nbr_length(i, 10); dprintf(1, " "), a++);
        dprintf(1, "%d  %s", i, temp->date);
        for (size_t a = 0; a != 8 - strlen(temp->date); dprintf(1, " "), a++);
        dprintf(1, "%s\r\n", temp->data);
    }
}

char *builtin_input(pos_t *t, char *command)
{
    char *temp = command;

    if (strncmp(command, "!", strlen("!")) == 0) {
        temp = flag_excla(t, command);
        if (temp == NULL) {
            temp = command;
            temp = strdup(temp += strlen(temp) - 1);
            free(command);
            return (temp);
        }
    }
    return (temp);
}
