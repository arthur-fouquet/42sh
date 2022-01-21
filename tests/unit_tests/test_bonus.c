/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for bonus
*/

#include <criterion/criterion.h>
#include "definition.h"

void episaucerc(head_t *head);
void set_prompt(char **tab, head_t *head);

Test(load_rc, simple_test)
{
    head_t head= {NULL, NULL, NULL};

    episaucerc(&head);
    cr_expect_eq(0, 0);
}