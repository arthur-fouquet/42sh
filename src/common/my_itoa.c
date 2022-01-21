/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** My itoa
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int my_intlen(int nbr)
{
    int cmp = 0;

    for (; nbr > 0; cmp++, nbr /= 10);
    return (cmp);
}

char *itoa_neg(int i, int temp, char *result)
{
    char *res = NULL;

    temp *= -1;
    res = calloc(2, my_intlen(temp));
    for (; temp != 0; i++) {
        res[i] = temp % 10 + '0';
        temp /= 10;
    }
    res[i] = '-';
    res[i+1] = '\0';
    free(result);
    return (my_revstr(res));
}

char *my_itoa(int nbr)
{
    int i = 0;
    int temp = nbr;
    char *result = calloc(my_intlen(nbr) + 1 + !nbr, sizeof(char));

    if (temp == 0) {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if (nbr < 0)
        return (itoa_neg(i, temp, result));
    for (; temp != 0; i++) {
        result[i] = temp % 10 + '0';
        temp /= 10;
    }
    result[i] = '\0';
    return (my_revstr(result));
}