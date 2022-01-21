/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** locate_command.c
*/

#include <stdbool.h>
#include "built_ins.h"
#include "common.h"
#include "exec.h"

static const char WHERE_MSG[] = " is a shell built-in";
static const char WHICH_MSG[] = ": shell built-in command.";

static const char *BUILT_INS[] =
{
    "where",
    "which",
    "cd",
    "env",
    "setenv",
    "unsetenv",
    "foreach",
    "if",
    "repeat",
    "exit",
    "echo",
    NULL
};

void print_path(char **tab, bool where, char *str)
{
    int w = 0;
    int perm = -1;
    bool ok = false;

    for (; tab[w] != NULL; w++) {
        perm = access(tab[w], F_OK);
        if (!perm) {
            dprintf(1,"%s\n", tab[w]);
            ok = true;
        }
        if (!perm && !where)
            break;
    }
    if (ok == false) {
        dprintf(2, "%s: Command not found.\n", str);
        return_value(1);
    }
}

void where_which_func(char *str, bool where)
{
    char *path = strdup(getenv("PATH"));
    char **tab = my_str_to_array(path, ':');

    if (tab == NULL) {
        dprintf(2, "%s: Command not found.\n", str);
        return_value(1);
        return;
    }
    for (int a = 0; tab[a] != NULL; a++) {
        tab[a] = strdup(tab[a]);
        tab[a] = realloc(tab[a], strlen(tab[a]) + strlen(str) + 2);
        tab[a] = strcat(strcat(tab[a], "/"), str);
    }
    print_path(tab, where, str);
    for (int a = 0; tab[a] != NULL; a++)
        free(tab[a]);
    free(tab);
    free(path);
}

bool is_shell_built_in(char *str, bool where)
{
    const char *msg = (where ? WHERE_MSG : WHICH_MSG);

    for (int a = 0; BUILT_INS[a] != NULL; a++)
        if (strcmp(BUILT_INS[a], str) == 0) {
            dprintf(2, "%s%s\n", BUILT_INS[a], msg);
            return (true);
        }
    return (false);
}

void where_which(char **tab, head_t *head)
{
    bool where = !strcmp(tab[0], "where");
    alias_t *alias = NULL;

    return_value(0);
    if ((tab = kill_all_quotes(handle_glob(tab))) == NULL)
        return (void)return_value(1);
    if (my_tablen(tab) < 2) {
        dprintf(2, "%s: Too few arguments.\n", tab[0]);
        return (void)return_value(1);
    }
    for (int a = 1; tab[a]; a++) {
        alias = get_alias(head->alias, tab[a]);
        if (alias != NULL)
            dprintf(1, "%s is aliased to %s\n", alias->alias, alias->command);
        if (alias != NULL && !where)
            return;
        if (is_shell_built_in(tab[a], where) == true && !where)
            continue;
        where_which_func(tab[a], where);
    }
}
