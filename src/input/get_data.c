/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_data.c
*/

#include "input.h"
#include "magical_value.h"
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

int get_cursor_position(v2i_t *c)
{
    char buf[32];
    index_t i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return (-1);
    do {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        i++;
    } while (buf[i-1] != 'R');
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[')
        return (-1);
    if (sscanf(&buf[2], "%d;%d", &c->y, &c->x) != 2)
        return (-1);
    return (0);
}

int get_window_size(v2i_t *win)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return (-1);
    } else {
        win->x = ws.ws_col;
        win->y = ws.ws_row;
        return (0);
    }
}

char *get_time(void)
{
    char *str = NULL;
    unsigned int length = 2;
    time_t raw_time;
    struct tm * time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);
    str = asctime(time_info);
    if (str[strcspn(str, ":") - 2] == '0')
        length = 1;
    str += strcspn(str, ":") - length;
    str[3+length] = '\0';
    return (strdup(str));
}