/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Exit function
*/

#include <ctype.h>
#include <stdio.h>
#include "definition.h"
#include "input.h"
#include "common.h"
#include "exec.h"

static int verify_number(char *nb, int neg)
{
    int nbr = 0;
    int status = 0;

    for (; *nb; nb++) {
        nbr += (status = !isdigit(*nb));
        if (status && (neg || nbr))
            return dprintf(2, "exit: Badly formed number.\n");
        if (status)
            return dprintf(2, "exit: Expression Syntax.\n");
    }
    return 0;
}

int verify_argument(char **arg)
{
    int neg = 0;
    char *tmp = strdup(arg[1]);

    if (*tmp == '-') {
        neg = 1;
        tmp++;
    }
    if (my_tablen(arg) > 2 || (!isdigit(*tmp) && !neg))
        return dprintf(2, "exit: Expression Syntax.\n");
    return verify_number(tmp, neg);
}

void exit_cmd(char **arg, head_t *head)
{
    arg = kill_all_quotes(handle_glob(arg));
    if (arg == NULL)
        return (void)(return_value(1));
    if (my_tablen(arg) == 1) {
        free(head->cmd);
        free_head(head);
        if (isatty(0))
            dprintf(1, "exit\n");
        exit_term();
        exit(0);
    }
    if (verify_argument(arg))
        return (void)(return_value(1));
    free(head->cmd);
    free_head(head);
    if (isatty(0))
        dprintf(1,"exit\n");
    exit_term();
    exit(atoi(arg[1]));
}
