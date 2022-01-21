/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Replace alias with real command
*/

#include "definition.h"
#include "common.h"
#include "exec.h"
#include <stdio.h>
#include <string.h>

static bool verify_loop(alias_t *head, alias_t *node)
{
    while (head != node) {
        if (!strcmp(head->alias, node->command))
            return true;
        head = head->next;
    }
    return false;
}

int replace_cmd(cmd_t *cmd, alias_t *alias)
{
    char *tmp = NULL;
    alias_t *head = alias;
    bool exist = false;

    while (alias) {
        if (!strncmp(cmd->args, alias->alias, strlen(alias->alias))) {
            tmp = (&cmd->args[strlen(alias->alias)]);
            cmd->args = my_strcat(alias->command, tmp, false, false);
            exist = verify_loop(head, alias);
            alias = head;
        }
        if (exist)
            return dprintf(2, "Alias loop.\n");
        alias = alias->next;
    }
    return 0;
}

int replace_alias(cmd_t *cmd, alias_t *alias)
{
    while (cmd) {
        if (replace_cmd(cmd, alias))
            return_value(1);
        cmd = cmd->next;
    }
    return (return_value(0));
}