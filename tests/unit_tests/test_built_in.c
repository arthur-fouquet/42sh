/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for built-ins
*/

#include <criterion/criterion.h>
#include "definition.h"
#include "parser.h"
#include "exec.h"
#include "common.h"
#include "built_ins.h"

cmd_t *parser(char *str);

int verify_argument(char **arg);
int replace_env_vars(head_t *head, char **str);

Test(create_alias, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"alias", "ls", "echo", NULL};
    char *tab2[] = {"alias", "ls", "echonope", NULL};
    char *tab3[] = {"alias", "a", "b"};
    char *tab4[] = {"alias", "ls", NULL};
    char *tab5[] = {"alias", NULL};
    char *tab6[] = {"alias", "test", NULL};
    char *tab7[] = {"unalias", "test", "ls", "lol", NULL};
    alias_t *test = NULL;

    create_alias(tab1, &head);
    create_alias(tab2, &head);
    create_alias(tab3, &head);
    create_alias(tab4, &head);
    create_alias(tab5, &head);
    create_alias(tab6, &head);
    test = get_alias(head.alias, "ls");
    cr_expect_str_eq(test->alias, "ls");
    cr_expect_str_eq(test->command, "echonope");
    cr_expect_null(get_alias(head.alias, "pute"));
    unset_alias(tab7, &head);
}

Test(replace_alias, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"alias", "ls", "echo", NULL};
    char *cmd = "ls pute && super okay";
    int ret = 0;

    create_alias(tab1, &head);
    head.cmd = parser(cmd);
    ret = replace_alias(head.cmd, head.alias);
    cr_expect_eq(ret, 0);
    cr_expect_str_eq(head.cmd->args, "echo pute");
}

Test(replace_env, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *cmd = strdup("echo $USER && echo $?");
    char *ref = my_strcat("echo ", getenv("USER"), false, false);
    int ret = 0;

    ref = my_strcat(ref, " && echo 0", true, false);
    head.cmd = parser(cmd);
    ret = replace_env_vars(&head, &cmd);
    cr_expect_eq(ret, 0);
    cr_expect_str_eq(ref, cmd);
}

Test(create_local_env, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"set", strdup("ls=4"), strdup("echo=4"), NULL};
    char *tab2[] = {"set", NULL};
    char *tab3[] = {"set", strdup("lol=aaa"), strdup("echo=69"), NULL};
    char *tab4[] = {"unset", "lol", "echo", "ls", NULL};

    create_local_env(tab1, &head);
    create_local_env(tab2, &head);
    create_local_env(tab3, &head);
    unset_local_env(tab4, &head);
}

Test(echo, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"echo", NULL};
    char *tab2[] = {"echo", "bite", NULL};
    char *tab3[] = {"echo", "puteasse", "lol", NULL};
    char *tab4[] = {"echo", "pute", "", NULL};

    echo(tab1, &head);
    echo(tab2, &head);
    echo(tab3, &head);
    echo(tab4, &head);
}

Test(cd, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"cd", NULL};
    char *tab2[] = {"cd", strdup("bite"), NULL};
    char *tab3[] = {"cd", strdup("ppute"), strdup("lol"), NULL};
    char *tab4[] = {"cd", strdup("~"), NULL};
    char *tab5[] = {"cd", strdup("-"), NULL};

    cd_fct(tab1, &head);
    cd_fct(tab2, &head);
    cd_fct(tab3, &head);
    cd_fct(tab4, &head);
    cd_fct(tab5, &head);
}

Test(exit_verify_argument, simple_test)
{
    char *tab1[] = {"exit", "a", NULL};
    char *tab2[] = {"exit", "45", NULL};
    char *tab3[] = {"exit", "1-", NULL};
    char *tab4[] = {"exit", "-&r", NULL};
    char *tab5[] = {"exit", "-34545", NULL};

    cr_expect_eq((verify_argument(tab1) != 0), 1);
    cr_expect_eq((verify_argument(tab2) == 0), 1);
    cr_expect_eq((verify_argument(tab3) != 0), 1);
    cr_expect_eq((verify_argument(tab4) != 0), 1);
    cr_expect_eq((verify_argument(tab5) == 0), 1);
}

Test(setenv, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"setenv", NULL};
    char *tab2[] = {"setenv", strdup("bite"), NULL};
    char *tab3[] = {"setenv", strdup("ppute"), strdup("lol"), NULL};
    char *tab4[] = {"setenv", strdup("lol"), strdup("lol"),
                    strdup("lol"), NULL};
    char *tab7[] = {"setenv", strdup("4"), NULL};
    char *tab8[] = {"setenv", strdup("a#{["), NULL};
    char *tab5[] = {"unsetenv", strdup("bite"), NULL};
    char *tab6[] = {"unsetenv", strdup("lol"), NULL};

    my_setenv(tab1, &head);
    my_setenv(tab2, &head);
    my_setenv(tab3, &head);
    my_setenv(tab4, &head);
    my_setenv(tab7, &head);
    my_setenv(tab8, &head);
    my_unsetenv(tab5, &head),
    my_unsetenv(tab6, &head);
}

Test(where_which, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"where", NULL};
    char *tab2[] = {"where", "ls", NULL};
    char *tab3[] = {"where", "ls", "echo", NULL};
    char *tab4[] = {"where", "mv", "ls", "echo", "gateau", NULL};
    char *tab5[] = {"which", "ls", "where", NULL};
    char *tab6[] = {"which", NULL};
    char *tab7[] = {"which", "alalal"};

    where_which(tab1, &head);
    where_which(tab2, &head);
    where_which(tab3, &head);
    where_which(tab4, &head);
    where_which(tab5, &head);
    where_which(tab6, &head);
    where_which(tab7, &head);
}

Test(repeat, simple_test)
{
    head_t head = {NULL, NULL, NULL};
    char *tab1[] = {"repeat", NULL};
    char *tab2[] = {"repeat", "ls", NULL};
    char *tab3[] = {"repeat", "4", "echo", NULL};
    char *tab4[] = {"repeat", "a", "mod", "echo", "gateau", NULL};
    char *tab5[] = {"repeat", "3b", "where", NULL};
    char *tab6[] = {"repeat", "3", "aaaa", NULL};
    char *tab7[] = {"repeat", "alalal"};

    repeat(tab1, &head);
    repeat(tab2, &head);
    repeat(tab3, &head);
    repeat(tab4, &head);
    repeat(tab5, &head);
    repeat(tab6, &head);
    repeat(tab7, &head);
}