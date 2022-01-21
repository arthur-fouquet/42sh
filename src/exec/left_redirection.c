/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** left_redirection.c
*/

#include <stdio.h>
#include <fcntl.h>
#include "common.h"
#include "parser.h"
#include "exec.h"

void my_simple_reverse_redirection(head_t *head, int fd, int stdout,
    UNUSED int in_fd)
{
    fd = open(head->cmd->next->args, O_RDONLY);
    if (fd == -1) {
        dprintf(2, "%s: %s.\n", head->cmd->next->args, strerror(errno));
        head->cmd = head->cmd->next;
        return;
    }
    dup2(fd, 0);
    close(fd);
    set_exec(head, 0);
    dup2(stdout, 0);
    head->cmd = head->cmd->next;
}

char *file_str(char *param)
{
    char *str = calloc(1, sizeof(char));
    char *rd = NULL;
    size_t size = 0;

    str[0] = '\0';
    while (42) {
        printf("? ");
        getline(&rd, &size, stdin);
        if (strncmp(rd, param, strlen(rd) - 1) == 0) {
            free(rd);
            break;
        }
        str = realloc(str, strlen(str) + strlen(rd) + 1);
        str = strcat(str, rd);
        free(rd);
        rd = NULL;
    }
    return (str);
}

void my_double_reverse_redirection(head_t *head)
{
    char *str = file_str(head->cmd->next->args);
    int cpy_stdin = dup(0);
    int fd = open("/tmp/redirect", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if (fd < 0)
        return (void)dprintf(2, "Error open.\n");
    write(fd, str, strlen(str));
    close(fd);
    free(str);
    if ((fd = open("/tmp/redirect", O_RDONLY)) < 0)
        return (void)dprintf(2, "Error open.\n");
    dup2(fd, 0);
    close(fd);
    set_exec(head, 0);
    dup2(cpy_stdin, 0);
    head->cmd = head->cmd->next;
}

void my_reverse_redirection(head_t *head, int in_fd)
{
    int stdout_copy = dup(1);
    int fd = 0;

    (void) in_fd;
    if (head->cmd->sep[1] != '<') {
        concate_args(&head);
        if (head->cmd->next != NULL)
            my_simple_reverse_redirection(head, fd, stdout_copy, in_fd);
    }
    else if (head->cmd->sep[1] == '<') {
        if (head->cmd->next != NULL)
            my_double_reverse_redirection(head);
    }
}
