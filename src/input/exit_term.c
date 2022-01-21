/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Exit terminal
*/

#include "input.h"
#include "die.h"

void exit_term(void)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr exit");
}
