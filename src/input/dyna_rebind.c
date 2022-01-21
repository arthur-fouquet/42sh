/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** dyna_rebind.c
*/

#include <dirent.h>
#include "common.h"
#include "input.h"

void change_dir(pos_t *t, char ch)
{
    int nbr_time = 1;

    if (ch != '/')
        return;
    if (t->in_tab == true)
        nbr_time--;
    for (int a = 0; a != nbr_time; a++)
        pop_queue(&t->dir);
}

char *get_last_arg(pos_t *t)
{
    char *ret = strrchr(t->buffer[t->ind], ' ');
    return (++ret);
}

static void move_command(pos_t *t, struct dirent *name, size_t len, int length)
{
    char *args = NULL;

    for (int i = len; i != t->win.x + 1; i++)
        t->buffer[t->ind][i] = 0;
    t->buffer[t->ind] = strcat(t->buffer[t->ind], name->d_name + length);
    if (name->d_type == DT_DIR)
        t->buffer[t->ind] = strcat(t->buffer[t->ind], "/");
    if (name->d_type == DT_REG)
        t->buffer[t->ind] = strcat(t->buffer[t->ind], " ");
    t->c.x = (int) strlen(t->buffer[t->ind]) + 1;
    print_buffer(t);
    args = get_last_arg(t);
    push(t, (queue_t) {args, length, NULL});
}

int dyna_rebind(pos_t *t, struct dirent **list, int n)
{
    int temp = n;
    char *cmd = get_last_arg(t);

    if (cmd[0] == 0 || t->in_tab == true || cmd[strlen(cmd) - 1] == '/')
        return (0);
    for (size_t nbr = strlen(cmd); n--;) {
        if (strncmp(cmd, list[n]->d_name, nbr) == 0) {
            move_command(t, list[n], strlen(t->buffer[t->ind]), nbr);
            return (1);
        } else if (n == 0) {
            n = temp;
            nbr--;
        }
        if (nbr == 0)
            break;
    }
    return (0);
}