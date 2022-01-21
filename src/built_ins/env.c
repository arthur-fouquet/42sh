/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** All_env_functions
*/

#include <ctype.h>
#include "built_ins.h"
#include "common.h"
#include "exec.h"

extern char **environ;
static const char *TOO_MANY_ARGS = "setenv: Too many arguments.\n";
static const char *FIRST_ALPHA = "setenv: Variable name must "
    "begin with a letter.\n";

static void put_bzero(char *env)
{
    for (int i = 0; env[i]; i++)
        if (env[i - 1] == '=' && env[i] == ' ' && env[i + 1] == '\0')
            env[i] = '\0';
}

void my_env(UNUSED char **tab, UNUSED head_t *head)
{
    char **env = environ;

    for (int n = 0; env[n] != NULL; n++) {
        put_bzero(env[n]);
        dprintf(1, "%s\n", env[n]);
    }
    return_value(0);
}

void my_setenv(char **name, head_t *head)
{
    int n = 0;

    name = kill_all_quotes(handle_glob(name));
    n = my_tablen(name);
    if (n > 3) {
        return_value(1);
        return (void)dprintf(2, "%s", TOO_MANY_ARGS);
    }
    if (n == 1)
        return my_env(name, head);
    if (isalpha(name[1][0]) == 0)
        return (void)dprintf(2, "%s", FIRST_ALPHA);
    if (str_is_alpha_num(name[1], name[0]))
        return (void)return_value(1);
    if (setenv(name[1], name[2] == NULL ? " " : name[2], 1) == -1) {
        dprintf(2, "setenv: %s.\n", strerror(errno));
        return_value(1);
    }
}

void my_unsetenv(char **name, UNUSED head_t *head)
{
    int n = 1;

    name = kill_all_quotes(handle_glob(name));
    if (name == NULL)
        return (void)return_value(1);
    if (my_tablen(name) < 2) {
        dprintf(2, "unsetenv: Too few arguments.\n");
        return (void)return_value(1);
    }
    while (name[n] != NULL) {
        unsetenv(name[n]);
        n++;
    }
    return_value(0);
}
