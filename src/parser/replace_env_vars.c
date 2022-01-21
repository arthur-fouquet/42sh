/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** replace_env_vars
*/

#include "definition.h"
#include "common.h"
#include "exec.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int my_intlen(int nbr);

static char *get_special_value(char *str)
{
    size_t sz = 0;
    char *tmp = NULL;

    for (; str[sz] && str[sz] != ' ' && str[sz] != '"'; sz++);
    tmp = calloc((sz + 1), sizeof(*tmp));
    strncpy(tmp, str, sz);
    return tmp;
}

char *is_in_one_env(head_t *head, char *str, char token)
{
    alias_t *tmp = head->local_env;
    size_t before_space = 0;
    CLEAR(str) char *real_key;
    char *real_value;

    str += (*str == token);
    for (; str[before_space] && str[before_space] != ' '
        && str[before_space] != '\"'
        && isalnum(str[before_space]) != 0; before_space++);
    real_key = strdup(str);
    real_key[before_space] = 0;
    if ((tmp = get_alias(tmp, real_key)) != NULL)
        return tmp->command;
    else if ((real_value = getenv(real_key)) != NULL)
        return real_value;
    if (!strcmp(get_special_value(str), "?"))
        return (my_itoa(return_value(-1000)));
    return NULL;
}

char *replace_var(char *str, char *val, int pos)
{
    char *res = NULL;
    size_t var_len = 0;
    size_t new_alloc;

    for (;!var_len || (str[pos + var_len] && str[pos + var_len] != ' '
        && str[pos + var_len] != '\"'
        && isalnum(str[pos + var_len]) != 0); var_len++);
    new_alloc = strlen(val) - (var_len);
    new_alloc = (new_alloc > 0 ? new_alloc : 0);
    res = calloc(strlen(str) + new_alloc + 1, sizeof(char));
    *res = 0;
    strncpy(res, str, pos);
    strcpy(res + pos, val);
    strcpy(res + pos + strlen(val),
        str + pos + var_len + (*(str + pos + var_len) == '?'));
    free(str);
    return res;
}

static int var_errors(char *str, index_t pos)
{
    if (isalnum(str[pos + 1])) {
        for (int j = 1; str[j + pos] && NOT_QUOTE(str[j + pos]); j++)
            printf("%c", str[j + pos]);
        printf(": Undefined variable.\n");
    } else
        printf("Illegal variable name.\n");
    return -1;
}

int replace_env_vars(head_t *head, char **str)
{
    char *val;

    if (strlen(*str) != 0 && (*str)[strlen(*str) - 1] == '\n')
        (*str)[strlen(*str) - 1] = '\0';
    for (index_t i = 0; (*str)[i]; i++) {
        if ((*str)[i] == '$'
            && (val = is_in_one_env(head, *str + i, '$')) != NULL) {
            *str = replace_var(*str, val, i);
        } else if ((*str)[i] == '$' && (*str)[i + 1] != '?')
            return var_errors(*str, i);
    }
    return 0;
}