/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for execution
*/

#include <criterion/criterion.h>
#include "definition.h"
#include "common.h"
#include "built_ins.h"
#include "parser.h"
#include "exec.h"

cmd_t *parser(char *str);

void check_return_exec(int status);

Test(return_value, simple_test)
{
    for (int i = 0; i != 255; i++)
        check_return_exec(i);
    cr_expect_eq(0, 0);
}

Test(kill_quote, simple_test)
{
    char *my = strdup("echo \"$USER\"");
    char *ref = "echo $USER";
    kill_quote(my);

    cr_expect_str_eq(my, ref);
}

Test(exec, simple_test)
{
    head_t head = {NULL, NULL, NULL};

    head.cmd = parser(strdup("ls && echo pute | cat"));
    exec_order(&head);
    cr_expect_eq(0, return_value(-1000));
    head.cmd = parser(strdup("ls && echo pute > test"));
    exec_order(&head);
    cr_expect_eq(0, return_value(-1000));
    head.cmd = parser(strdup("rm test < toto"));
    exec_order(&head);
    cr_expect_eq(0, return_value(-1000));
    head.cmd = parser(strdup("cat < main.c"));
    exec_order(&head);
    cr_expect_eq(0, return_value(-1000));
}