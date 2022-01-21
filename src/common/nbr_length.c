/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Get the length of a number
*/

int nbr_length(int nbr, int base)
{
    int a = nbr / base;
    int b = 0;

    for (; a > 0; b++, a = a / base);
    return (b + 1);
}