/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** execution.c
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "exec.h"
#include "die.h"

extern char **environ;

int return_value(int value)
{
    static int rtn = 0;

    if (value != -1000)
        rtn = value;
    return (rtn);
}

void print_error(char *str)
{
    dprintf(2, "%s: %s", str, strerror(errno));
    if (errno == ENOEXEC)
        dprintf(2, ". Wrong Architecture");
    dprintf(2, ".\n");
}

void check_return_exec(int status)
{
    int return_val = 0;

    if (WIFEXITED(status))
        return_val = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        return_val = WTERMSIG(status);
        if (return_val == 11)
            dprintf(2, "Segmentation fault");
        if (return_val == 6)
            dprintf(2, "Abort");
        if (return_val == 8)
            dprintf(2, "Floating exception");
        if (WCOREDUMP(status))
            dprintf(2, " (core dumped)");
        dprintf(2, "\n");
    }
    return_value(return_val);
}

void exec_function(char *str, char **tab)
{
    pid_t pid = fork();
    pid_t waiter;
    int status = 0;

    if (pid == 0) {
        if (execve(str, tab, environ) == -1) {
            print_error(tab[0]);
            exit(1);
        }
    } else if (pid > 0) {
        waiter = waitpid(pid, &status, 0);
        if (waiter < 0) {
            dprintf(2, "%s: %s.\n", tab[0], strerror(errno));
            exit(84);
        }
        check_return_exec(status);
    } else {
        dprintf(2, "%s: %s.\n", tab[0], strerror(errno));
        exit(84);
    }
}
