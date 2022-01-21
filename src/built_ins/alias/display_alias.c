/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Display alias
*/

#include <stdio.h>
#include <string.h>
#include "alias.h"

void display_alias(alias_t *alias)
{
    while (alias) {
        printf("%s\t", alias->alias);
        if (alias->par)
            printf("(");
        printf("%s", alias->command != NULL ? alias->command : "");
        if (alias->par)
            printf(")");
        printf("\n");
        alias = alias->next;
    }
}

alias_t *get_alias(alias_t *alias, char *wanted)
{
    if (wanted == NULL)
        return NULL;
    while (alias) {
        if (!strcmp(alias->alias, wanted))
            return alias;
        alias = alias->next;
    }
    return NULL;
}

void display_one_alias(alias_t *head, char *cmd)
{
    alias_t *alias = get_alias(head, cmd);

    if (alias == NULL)
        return;
    printf("%s %s\n", alias->alias, alias->command);
}