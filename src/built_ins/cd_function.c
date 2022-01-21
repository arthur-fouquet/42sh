/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** cd_function.c
*/

#include "built_ins.h"
#include "common.h"
#include "exec.h"

static const char *NO_HOME = ": No home directory.\n";
static const char *NO_DIR = ": No such file or directory.\n";

static void check_path(char **str)
{
    char *path = NULL;
    char const *env_var = (*(*str) == '-' ? "OLDPWD" : "HOME");

    if ((*str)[0] != '~' && (*str)[0] != '-')
        return;
    path = getenv(env_var);
    if (path == NULL)
        return;
    path = strdup(path);
    shift_str(str);
    path = realloc(path, strlen(path) + strlen(*str) + 1);
    strcat(path, (*str));
    free(*str);
    (*str) = strdup(path);
    free(path);
}

void print_cd_error(char **str)
{
    if ((*str)[0] == '~')
        dprintf(2, "No $home variable set.\n");
    else if ((*str)[0] == '-')
        dprintf(2, "%s", NO_DIR);
    else
        dprintf(2, "%s: %s.\n", *str, strerror(errno));
}

static void cd(char **str, head_t *head)
{
    char *tab_old[4] = {"setenv", "OLDPWD", getcwd(NULL, 0), NULL};
    char *tab_new[4] = {"setenv", "PWD", NULL, NULL};

    check_path(str);
    if (chdir(*str) == -1) {
        print_cd_error(str);
        return_value(1);
        return;
    }
    my_setenv(tab_old, head);
    tab_new[2] = getcwd(NULL, 0);
    my_setenv(tab_new, head);
    free(tab_old[2]);
    free(tab_new[2]);
    return_value(0);
}

void cd_fct(char **tab, head_t *head)
{
    char *str = NULL;

    tab = kill_all_quotes(handle_glob(tab));
    if (tab == NULL)
        return (void)return_value(1);
    if (my_tablen(tab) > 2) {
        dprintf(2, "cd: Too many arguments.\n");
        return (void)return_value(1);
    }
    if (tab[1] == NULL) {
        str = getenv("HOME");
        if (str == NULL) {
            dprintf(2, "cd%s", NO_HOME);
            return (void)return_value(1);
        }
        str = strdup(str);
        cd(&str, head);
        free(str);
    } else
        cd(&tab[1], head);
}
