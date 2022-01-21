/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** exec.h
*/

#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "definition.h"

int return_value(int value);

// * Redirection
void my_reverse_redirection(head_t *head, int fd);
void my_redirection(head_t *head, int fd);

// * Separator
void exec_pipe(head_t *head, int fd);
void and_or(head_t *cmd, int fd);

// * Execution
void set_exec(head_t *head, int fd);
void exec_order(head_t *head);
int get_exec(char **str, char *cmd);

char **handle_glob(char **command);

// * Alias
int replace_alias(cmd_t *cmd, alias_t *alias);

#define BAD_RED\
    (((*node)->sep[0] == '<' || (*node)->sep[0] == '>') &&     \
    strcmp((*node)->sep, (*node)->next->sep) == 0)

#define BAD_PIPE\
    (strcmp((*node)->sep, "|") == 0 && (*node)->next->sep[0] == '<')

#define NEXT_EXIST\
    *node != NULL && (*node)->sep != NULL && (*node)->next != NULL && \
    (*node)->next->sep != NULL

#endif
