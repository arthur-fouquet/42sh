/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** control_tower.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "parameters.h"
#include "input.h"
#include "die.h"

void change_dir(pos_t *t, char ch);

void add_char(char ch, pos_t *t)
{
    if (iscntrl(ch) && ch != 127 && ch != 9)
        return;
    if (ch == 9) {
        dprintf(1 , "\n\r");
        auto_comp(t);
    }
    if (ch == 127 && t->c.x - 1 != (int) strlen(t->prompt)) {
        change_dir(t, t->buffer[t->ind][CUR_TO_IND(t->c.x)]);
        shift_to_left(t->buffer[t->ind], CUR_TO_IND(t->c.x));
        (t->c.x - 1 != 0) ? t->c.x -= 1 : t->c.x;
        dprintf(1, "\x1b[0J\r");
        dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
        t->nbr_time = -1;
    } else if (ch != 127 && ch != 9) {
        shift_to_right(t->buffer[t->ind], CUR_TO_IND(t->c.x) + 1, ch);
        t->c.x += 1;
    }
    print_buffer(t);
}

static int command_ctrl(char ch, pos_t *t)
{
    if (CTRL_KEY('d') == ch) {
        list_delete(&t->h.history);
        free(t->buffer[t->ind]);
        exit_term();
        exit(0);
    } else if (CTRL_KEY('l') == ch) {
        CTRL_L(STDOUT_FILENO);
        t->c.y = 0;
        print_buffer(t);
        return (1);
    }
    if (CTRL_KEY('c') == ch) {
        t->buffer[t->ind] = memset(t->buffer[t->ind], 0, t->win.x + 1);
        t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->prompt);
        t->c.x = (int) strlen(t->prompt) + 1;
        t->c.y += 1;
        print_buffer(t);
    } else if (CTRL_KEY('p') == ch)
        handle_history(t, 'A');
    return (0);
}

static void go_to_newline(pos_t *t)
{
    t->c.y += 1;
    t->c.x = 1;
    t->ind++;
    t->buffer[t->ind] = calloc(t->win.x + 1, sizeof(char));
    if (t->buffer[t->ind] == NULL)
        die("calloc");
    t->buffer[t->ind] = memset(t->buffer[t->ind], 0, t->win.x + 1);
    print_buffer(t);
}

static int press_enter(pos_t *t)
{
    char *tmp = NULL;

    if (t->in_tab == true) {
        dprintf(1, "\x1b[0J\r");
        dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
        t->in_tab = false;
        t->nbr_time = -1;
        tmp = strrchr(t->buffer[t->ind], ' ');
        tmp++;
        push(t, (queue_t) {tmp,
            strlen(t->buffer[t->ind]), NULL});
        return (0);
    }
    t->h.index = 0;
    dprintf(1, "\r\n");
    exit_term();
    return (1);
}

int command_char(char ch, pos_t *t)
{
    if (t->c.x == t->win.x + 1)
        go_to_newline(t);
    if (command_ctrl(ch, t) == 1)
        return (0);
    if (CTRL_KEY('m') == ch)
        return (press_enter(t));
    if (ch == ESCAPE) {
        dprintf(1, "\x1b[0J\r");
        dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
        t->in_tab = false;
        t->nbr_time = -1;
        move_cursor(t);
    }
    else if (ch != 0)
        add_char(ch, t);
    return (0);
}
