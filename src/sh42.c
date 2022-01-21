/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** 42sh
*/

#include <stdio.h>
#include "parser.h"
#include "common.h"
#include "exec.h"
#include "input.h"
#include "die.h"

extern char **environ;

int replace_env_vars(head_t *head, char **str);
cmd_t *parser(char *str);
void episaucerc(head_t *head);
void prompt(char **str, head_t *head);

static void back_term(pos_t *t, char *str)
{
    if (str != NULL)
        free(str);
    if (isatty(0) == 0)
        return;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->raw) == -1)
        die("tcsetattr");
    if (get_cursor_position(&t->c) == -1)
        die("get_cursor_position");
    t->ind = 0;
    t->c.x = strlen(t->prompt) + 1;
    for (int a = 0; t->buffer[a]; a++)
        t->buffer[a] = memset(t->buffer[a], 0, t->win.x + 1);
    t->buffer[t->ind] = strcpy(t->buffer[t->ind], t->prompt);
    for (; t->dir != NULL; pop_queue(&t->dir));
    dprintf(1, "\r%s\r", t->buffer[t->ind]);
    dprintf(1, "\x1b[%d;%dH", t->c.y, t->c.x);
}

int shell(void)
{
    pos_t t;
    head_t head = {NULL, NULL, NULL, &t};
    size_t sz = 0;
    char *str = NULL;

    episaucerc(&head);
    init_terminal(&t);
    while (!((str = input(&t)) == NULL && getline(&str, &sz, stdin) == -1)) {
        if (strlen(str) == 1 || replace_env_vars(&head, &str) == -1 ||
        !(head.cmd = parser(str)) || replace_alias(head.cmd, head.alias)) {
            prompt(&(t.prompt), &head);
            back_term(&t, str);
            continue;
        }
        exec_order(&head);
        free_list(head.cmd);
        prompt(&(t.prompt), &head);
        back_term(&t, str);
    } free_head(&head);
    return 0;
}
