/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Disable quote for simple exec
*/

#include "built_ins.h"
#include "magical_value.h"

char **kill_all_quotes(char **tab)
{
    if (tab != NULL)
        for (index_t i = 0; tab[i] != NULL; i++)
            kill_quote(tab[i]);
    return tab;
}