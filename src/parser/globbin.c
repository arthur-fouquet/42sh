/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Handle globbing
*/

#include <glob.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int error(char *s, int i)
{
    return dprintf(2, "%s : %d\n", s, i);
}

bool is_wildcard(const char *str)
{
    bool asterisk;
    bool question;
    int regex = 0;

    if (*str == '\"' || *str == '\'' || *str == '`')
        return false;
    for (int i = 0; str[i]; i++) {
        regex += ((!regex && str[i] == '[')
                || (regex && (str[i] == ']' && str[i - 1] != '[')));
        asterisk = (str[i] == '*');
        question = (str[i] == '?');
        if ((regex == 2 || asterisk || question))
            return true;
    }
    return false;
}

char **replace_all(char **tab, int *j, glob_t *globs)
{
    int tab_len = 0;
    int new_vars_nb = globs->gl_pathc;
    char **new_vars = globs->gl_pathv;
    char **res = NULL;
    int i = 0;

    for (; tab[tab_len] != NULL; tab_len++);
    if ((res = malloc(sizeof(char *) * (tab_len + new_vars_nb))) == NULL)
        return NULL;
    for (; i < *j; i++) {
        res[i] = strdup(tab[i]);
    }
    for (; i < *j + new_vars_nb; i++)
        res[i] = new_vars[i - *j];
    for (int k = *j + 1; tab[k]; free(tab[k]), i++, k++)
        res[i] = strdup(tab[k]);
    res[i] = NULL;
    *j += new_vars_nb - 1;
    return res;
}

char **handle_glob(char **command)
{
    glob_t glob_s = {0};
    bool glob_b;

    if (command == NULL)
        return NULL;
    for (int i = 0; command[i]; i++) {
        glob_b = is_wildcard(command[i]);
        if (glob_b && glob(command[i], GLOB_TILDE,
        (int (*)(const char *, int)) error, &glob_s) != 0) {
            dprintf(2, "%s: No match.\n", command[0]);
            return NULL;
        } else if (glob_b)
            command = replace_all(command, &i, &glob_s);
    }
    return command;
}