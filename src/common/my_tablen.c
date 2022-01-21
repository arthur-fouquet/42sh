/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** my_tablen.c
*/

#include <stddef.h>

int my_tablen(char **tab)
{
    int size = 0;

    if (tab != NULL)
        for (; tab[size] != NULL; size++);
    return (size);
}
