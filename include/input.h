/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Input.h
*/

#ifndef INPUT_H
#define INPUT_H

// include
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include "linked_list.h"
#include "parameters.h"
#include "queue.h"

// typedef
#define PRINT(x) dprintf(2, "%s\r\n<%s>\r\n%s", KRED, x, RESET)
#define PRIND(x) dprintf(2, "\n\r%d\r\n", x)
#define PRINC(x) dprintf(2, "\n\r%c\r\n", x)

// structure
typedef struct v2i_s {
    int x;
    int y;
} v2i_t;

typedef struct history_s {
    dblist_t *history;
    int index;
    char *temp;
    bool first_time;
} hs_t;

typedef struct pos_s {
    v2i_t c;
    v2i_t win;
    char **buffer;
    int ind;
    struct termios raw;
    char *prompt;
    int nbr_time;
    bool in_tab;
    queue_t *dir;
    hs_t h;
} pos_t;

// data
struct termios orig_termios;

// main function
char *input(pos_t *t);
void exit_term(void);
void init_terminal(pos_t *t);
int push(pos_t *t, queue_t data);
int destroy_queue(queue_t **queue);

// builtin
char *builtin_input(pos_t *t, char *command);
void auto_comp(pos_t *t);

// print & special_key
int command_char(char ch, pos_t *t);
void move_cursor(pos_t *t);
void add_char(char ch, pos_t *t);
void print_buffer(pos_t *t);
void handle_history(pos_t *t, char seq);

// get data
int get_window_size(v2i_t *win);
int get_cursor_position(v2i_t *c);

#endif //PSU_42SH_2019_INPUT_H
