/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** prompt
*/

#include "input.h"
#include "definition.h"
#include "common.h"
#include "prompt.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *replace_var(char *str, char *val, int pos);
char *is_in_one_env(head_t *head, char *str, char delim);
char *get_current_dir_name(void);

char *(*options_functions[])(void) =
{
    prompt_git,
    prompt_user,
    prompt_pwd,
    NULL
};

static const char *options[] =
{
    "GIT",
    "USER",
    "PWD",
    NULL
};

char *prompt_git(void)
{
    return "|GIT|";
}

char *prompt_user(void)
{
    char *res = getenv("USER");

    return res == NULL ? NULL : strdup(res);
}

char *prompt_pwd(void)
{
    char *res = get_current_dir_name();
    char *home = getenv("HOME");
    int slash_c = 0;

    if (res == NULL)
        return NULL;
    if (home && strcmp(home, res) == 0)
        return strdup("~");
    for (int i = 0; res[i]; i++)
        slash_c += (res[i] == '/');
    if (slash_c != 1)
        for (; *res && slash_c; shift_str(&res))
            slash_c -= (*res == '/');
    return res;
}

char *get_prompt_var(char *str)
{
    str += (*str == '@');
    for (int i = 0; options[i]; i++)
        if (!strncmp(options[i], str, strlen(options[i]))){
            return options_functions[i]();
        }
    return NULL;
}

void prompt(char **str, UNUSED head_t *head)
{
    char *val;
    char *tmp;

    if ((tmp = getenv("PROMPT")) == NULL)
        return;
    *str = strdup(tmp);
    for (int i = 0; (*str)[i]; i++)
        if ((*str)[i] == '@' && (val = get_prompt_var(*str + i)) != NULL)
            *str = replace_var(*str, val, i);
}