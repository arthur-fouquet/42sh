/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** echo
*/

#include <string.h>
#include <stdio.h>
#include "common.h"
#include "definition.h"
#include "exec.h"

void echo(char **args, UNUSED head_t *head)
{
    bool n = (args[1] != NULL && !strcmp(args[1], "-n"));

    args = kill_all_quotes(handle_glob(args));
    if (args == NULL)
        return (void)(return_value(1));
    for (int i = 1 + (int)n; args[i] != NULL; i++) {
        dprintf(1, "%s", args[i]);
        if (args[i + 1] != NULL && strlen(args[i + 1]))
            dprintf(1, " ");
    }
    if (!n)
        dprintf(1, "\n");
    return_value(0);
}
