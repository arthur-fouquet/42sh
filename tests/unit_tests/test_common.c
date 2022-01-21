/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** UT for common file
*/

#include <criterion/criterion.h>
#include "common.h"

Test(my_itoa, simple_test)
{
    char *nb1 = my_itoa(10);
    char *nb2 = my_itoa(-23456);
    char *nb3 = my_itoa(234567);
    char *nb4 = my_itoa(234543);

    cr_expect_str_eq(nb1, "10");
    cr_expect_str_eq(nb2, "-23456");
    cr_expect_str_eq(nb3, "234567");
    cr_expect_str_eq(nb4, "234543");
}

Test(strconcat, simple_test)
{
    char *ref1 = my_strconcat_space("echo", "pute");

    cr_expect_str_eq(ref1, "echo pute");
}

Test(strconcat_bsn, simple_test)
{
    char *ref1 = my_strconcat_bsn("echo", "pute");

    cr_expect_str_eq(ref1, "echopute\n");
}

Test(shift_to_right, simple_test)
{
    char *buffer = strdup("echopute");

    shift_to_right(buffer, 4, ' ');
    cr_expect_str_eq(buffer, "echo pute");
}

