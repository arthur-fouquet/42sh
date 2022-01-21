/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** write_dir.c
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "parameters.h"
#include "input.h"

#define file list[a]->d_name

static void move_command(pos_t *t, struct dirent *name)
{
    size_t len = t->dir->cursor;

    for (int i = len; i != t->win.x + 1; i++)
        t->buffer[t->ind][i] = 0;
    t->buffer[t->ind] = strcat(t->buffer[t->ind], name->d_name);
    if (name->d_type == DT_REG)
        t->buffer[t->ind] = strcat(t->buffer[t->ind], " ");
    t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
    print_buffer(t);
}

static void print_file(struct dirent **list, const int *nbr, int a)
{
    size_t len = strlen(file);

    if (list[a]->d_type == DT_LNK)
        dprintf(1, "%s", KCYN);
    if (access(file, F_OK | X_OK) == 0)
        dprintf(1, "%s", KGRN);
    if (list[a]->d_type == DT_DIR) {
        dprintf(1, "%s", KBLU);
        dprintf(1, "%s", file);
        dprintf(1, "%s/", KWHT);
        file[len] = '/';
        file[len + 1] = '\0';
    } else
        dprintf(1, "%s", file);
    if (*nbr == a)
        dprintf(1, "%s <--", KWHT);
}

void write_dir(struct dirent **list, int *nbr_time, int n, pos_t *t)
{
    v2i_t temp;

    dprintf(1, "\x1b[0J\r");
    for (int a = 0; a != n; a++, dprintf(1, "%s\r\n", RESET))
        print_file(list, nbr_time, a);
    temp = t->c;
    get_cursor_position(&t->c);
    dprintf(1, "\x1b[?25h");
    if (t->c.y >= t->win.y) {
        t->c.y -= n + 1;
        dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
    } else
        t->c = temp;
    if (*nbr_time != -1)
        move_command(t, list[*nbr_time]);
    if (*nbr_time == n - 1)
        *nbr_time = -1;
    (*nbr_time)++;
}