/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Main function
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int shell(void);

extern char **environ;

int main(void)
{
    if (getenv("PATH") == NULL)
        setenv(strdup("PATH"), strdup("/usr/bin:/bin"), 1);
    return shell();
}
