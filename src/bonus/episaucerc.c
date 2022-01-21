/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** episaucerc
*/

#include <stdio.h>
#include "parser.h"
#include "common.h"
#include "exec.h"
#include "input.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

cmd_t *parser(char *str);

extern char **environ;

int replace_env_vars(head_t *head, char **str);

void end_of_line(char *str)
{
    int quotes[3] = {0, 0, 0};

    for (int i = 0; str[i]; i++) {
        UPDATE_QUOTES(quotes, str[i]);
        if (str[i] == '\n' || (str[i] == '#' && NOT_IN_QUOTES(quotes))) {
            str[i] = 0;
            return;
        }
    }
}

void episaucerc(head_t *head)
{
    size_t sz = 0;
    char *str = NULL;
    FILE *episauce_file = fopen("/tmp/.episaucerc", "r");

    if (episauce_file == NULL)
        return;
    while (getline(&str, &sz, episauce_file) != -1) {
        end_of_line(str);
        if (*str == '#' || (replace_env_vars(head, &str) == -1
            || (head->cmd = parser(str)) == NULL)) {
            continue;
        }
        exec_order(head);
        free_list(head->cmd);
    }
}