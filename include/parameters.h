/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** magical_number.c
*/

#ifndef MAGICAL_NUMBER_H
#define MAGICAL_NUMBER_H

// define
#define CTRL_KEY(k) ((k) & 0x1f)
#define CUR_TO_IND(x) (x - 2)

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\x1B[0m"

// values
static const char ESCAPE = '\x1b';

// Return value
static const int ERROR = 84;
static const int OK = 0;

// Comparison
static const int DIFF = 1;
static const int SAME = 0;

// Macros
#define EXIT_ERROR(x)                       \
                do {                        \
                    fprintf(stderr, x);     \
                    exit(84);               \
                } while (0)                 \

#define CTRL_L(x)                           \
        do {                                \
            dprintf(x, "\x1b[2J\r");        \
            dprintf(x, "\x1b[H\r");         \
        } while (0)                         \

int nbr_length(int nbr, int base);

#endif //PSU_42SH_2019_MAGICAL_NUMBER_H
