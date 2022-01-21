/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** repeat
*/

#include "built_ins.h"
#include "common.h"
#include "exec.h"

int exec(char **tab);

static const char *FEW_ARG = "repeat: Too few arguments.\n";
static const char *BAD_ARG = "repeat: Badly formed number.\n";

void exec_repeat(char **line)
{
    int n = 0;
    int end = 0;

    end = atoi(line[1]);
    while (n != end && line[1][0] != '-') {
        return_value(exec(line + 2) == -1);
        n++;
    }
}

void repeat(char **line, UNUSED head_t *head)
{
    int n = my_tablen(line);

    line = kill_all_quotes(handle_glob(line));
    if (line == NULL)
        return (void)return_value(1);
    if (n <= 2) {
        dprintf(2, "%s", FEW_ARG);
        return_value(1);
        return;
    }
    if (str_is_num(line[1]) == 1 && line[1][0] != '-') {
        dprintf(2, "%s", BAD_ARG);
        return_value(1);
        return;
    }
    exec_repeat(line);
}
