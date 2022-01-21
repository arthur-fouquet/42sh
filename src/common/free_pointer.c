/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Free pointer
*/

#include <stdlib.h>

void clear_str(char **p)
{
    if (*p != NULL)
        free(*p);
}

void clear_tab(char ***p)
{
    if (*p != NULL)
        free(*p);
}

void clear_full_tab(char ***p)
{
    if (*p != NULL) {
        for (int i = 0; (*p)[i] != NULL; free((*p)[i]), i++);
        free(*p);
    }
}
