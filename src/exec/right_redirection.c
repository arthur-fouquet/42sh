/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** right_redirection.c
*/

#include <fcntl.h>
#include "exec.h"
#include "parser.h"
#include "common.h"

void kill_quote(char *str);

void my_redirection_right(head_t *head, int fd, int stdout, bool shit)
{
    kill_quote(head->cmd->next->args);
    if (!shit)
        fd = open(head->cmd->next->args, O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (shit)
        fd = open(head->cmd->next->args, O_APPEND | O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd < 0) {
        dprintf(2, "Error open.\n");
        return (void)return_value(1);
    }
    dup2(fd, 1);
    close(fd);
    set_exec(head, 0);
    dup2(stdout, 1);
}

void concate_args(head_t **head)
{
    CLEAR(full_tab) char **str = get_parameters((*head)->cmd->next->args, ' ');
    int n = 1;

    while (str[n] != NULL && (*head)->cmd->next->next == NULL) {
        (*head)->cmd->args = my_strconcat_space((*head)->cmd->args , str[n]);
        (*head)->cmd->next->args = strdup(str[0]);
        n++;
    }
}

void my_redirection(head_t *head, UNUSED int in_fd)
{
    int stdout_copy = dup(STDOUT_FILENO);
    int fd = 0;

    concate_args(&(head));
    if (head->cmd->next != NULL)
        my_redirection_right(head, fd, stdout_copy, head->cmd->sep[1] == '>');
    head->cmd = head->cmd->next;
}
