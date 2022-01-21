/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** die.h
*/

#ifndef DIE_H
#define DIE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void exit_term(void);

#define die(x) _die(x, __func__)
static inline void _die(char const *what, char const *where)
{
    (void)what;
    (void)where;
    #ifdef DEBUG
    dprintf(2, "\e[0;1m[\e[0;94m%s\e[0;1m]@\e[0;1m[\e[0;94m%s\e[0;1m]:"
    "\e[0;1m[\e[0;94m%s\e[0;1m]\e[0m\n", what, where, strerror(errno));
    exit_term();
    #endif
    exit(errno ? 84 : 0);
}
#endif
