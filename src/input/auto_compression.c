/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** auto-compression.c
*/

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "die.h"
#include "common.h"
#include "input.h"

int dyna_rebind(pos_t *t, struct dirent **list, int n);
void write_dir(struct dirent **list, int *nbr_time, int n, pos_t *t);
char *get_last_arg(pos_t *t);


static int file_select(const struct dirent *entry)
{
    return (0 == (entry->d_name[0] == '.'));
}

static char *format_path(pos_t *t, char *elem)
{
    t->dir->path = calloc(strlen(elem) + 1, sizeof(char));

    t->dir->path = memset(t->dir->path, 0, strlen(t->dir->path) + 1);
    t->dir->path = strcpy(t->dir->path, elem);
    t->dir->cursor = (int) strlen(t->buffer[t->ind]);
    t->c.x = t->dir->cursor + 1;
    return (t->dir->path);
}

static char *get_path(pos_t *t)
{
    char *arg = get_last_arg(t);
    char *elem = calloc(strlen(arg) + 3, sizeof(char));
    struct stat fs;

    if (t->dir == NULL)
        push(t, (queue_t) {".",
            strlen(t->buffer[t->ind]), NULL});
    elem = strcpy(elem, "./");
    elem = strcat(elem, arg);
    if (t->in_tab == true)
        return (t->dir->path);
    if (lstat(elem, &fs) != -1)
        return (format_path(t, elem));
    else
        return (t->dir->path);
}

void auto_comp(pos_t *t)
{
    struct dirent **name_list;
    char *tmp = get_path(t);
    int n = scandir(tmp, &name_list, file_select, alphasort);

    if (n == -1)
        die("scandir");
    if (n == 0 || dyna_rebind(t, name_list, n) == 1)
        return;
    t->in_tab = true;
    write_dir(name_list, &t->nbr_time, n, t);
    for (int a = 0; a != n; a++)
        free(name_list[a]);
    free(name_list);
}