/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Exec function
*/

#include "common.h"
#include "built_ins.h"
#include "parser.h"
#include "exec.h"

void (*separator_functions[])(head_t *cmd, int fd) =
{
    my_reverse_redirection,
    my_reverse_redirection,
    my_redirection,
    my_redirection,
    exec_pipe,
    set_exec,
    set_exec,
    and_or,
    and_or,
};

static const char *SEPARATOR[] =
{
    "<",
    "<<",
    ">",
    ">>",
    "|",
    ";",
    "&",
    "&&",
    "||",
    NULL
};

int is_cmd_built_in(char **tab, head_t *head);
void exec_function(char *str, char **tab);

void and_or(head_t *head, int fd)
{
    int value = !1;
    bool dog = !1;
    bool ret = !1;

    set_exec(head, fd);
    value = return_value(-1000);
    dog = strcmp(head->cmd->sep, "||") == 0 ? true : false;
    ret = value == 0 ? true : false;
    while (head->cmd->next && head->cmd->sep && head->cmd->sep[0] != ';') {
        if ((dog && ret) || (!dog && !ret))
            head->cmd = head->cmd->next;
        else
            break;
    }
}

int exec(char **tab, head_t *head)
{
    char *cmd = NULL;

    if (is_cmd_built_in(tab, head) == 1)
        return (1);
    if (get_exec(&cmd, tab[0]) < 0)
        return (return_value(-1));
    tab = kill_all_quotes(handle_glob(tab));
    if (tab == NULL)
        return (return_value(-1));
    exec_function(cmd, tab);
    return (0);
}

void set_exec(head_t *head, UNUSED int fd)
{
    CLEAR(full_tab) char **tab = get_parameters(head->cmd->args, ' ');

    if (tab == NULL)
        return;
    for (int a = 0; tab[a] != NULL; a++)
        tab[a] = strdup(tab[a]);
    if (exec(tab, head) == -1)
        return_value(1);
}

static int check_redirections(cmd_t **node)
{
    void *first = (*node);

    while (NEXT_EXIST) {
        if (BAD_RED || BAD_PIPE) {
            dprintf(2, "Ambiguous input redirect.\n");
            return (-1);
        }
        if ((*node)->sep[0] == '>' && strcmp((*node)->next->sep, "|") == 0) {
            dprintf(2, "Ambiguous output redirect.\n");
            return (-1);
        }
        (*node) = (*node)->next;
    }
    (*node) = first;
    if ((*node)->args[0] == '\0') {
        dprintf(2, "Invalid null command.\n");
        return (-1);
    }
    return (0);
}

void exec_order(head_t *head)
{
    int a = 0;

    if (check_redirections(&(head->cmd)) == -1)
        return;
    while (head->cmd != NULL) {
        if (head->cmd->args[0] == '\0') {
            dprintf(2, "Invalid null command.\n");
            return_value(1);
            return;
        }
        for (a = 0; head->cmd->sep != NULL && SEPARATOR[a] != NULL &&
                strcmp(SEPARATOR[a], head->cmd->sep) != 0; a++);
        if (head->cmd->sep == NULL || SEPARATOR[a] == NULL)
            set_exec(head, 0);
        else
            separator_functions[a](head, 0);
        head->cmd = head->cmd->next;
    }
}
