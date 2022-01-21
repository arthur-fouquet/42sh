/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for header
*/

#include "parameters.h"
#include "common.h"
#include <criterion/criterion.h>
#include "definition.h"
#include "built_ins.h"

cmd_t *parser(char *str);

Test(nbr_lenght, simple_test)
{
    int result = nbr_length(420, 10);

    cr_expect_eq(result, 3);
}

Test(test_clear_str, simple_test)
{
    char *str = strdup("toto");

    clear_str(&str);
    cr_expect_eq(0, 0);
}

Test(test_clear_tab, simple_test)
{
    char **tab = calloc(4, sizeof(*tab));

    clear_tab(&tab);
    cr_expect_eq(0, 0);
}

Test(test_clear_full_tab, simple_test)
{
    char **tab = get_parameters(strdup("echo pute test"), ' ');

    clear_full_tab(&tab);
    cr_expect_eq(0, 0);
}

Test(free_list, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *alias[] = {"alias", "ls", "pute", NULL};
    char *local_env[] = {"set", "ls", "pute", NULL};

    head.cmd = parser(strdup("echo pute && echo yo ; salut"));
    create_alias(alias, &head);
    create_local_env(local_env, &head);

    free_head(&head);
    free_list(head.cmd);
}