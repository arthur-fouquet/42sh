/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Free list
*/

#include <stdlib.h>
#include "definition.h"

void free_list(cmd_t *list)
{
    cmd_t *tmp = NULL;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp->args);
        free(tmp->sep);
        free(tmp);
    }
}

void free_alias(alias_t *alias)
{
    alias_t *tmp = NULL;

    while (alias) {
        tmp = alias;
        alias = alias->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
    }
}

void free_head(head_t *head)
{
    free_alias(head->alias);
    free_alias(head->local_env);
}