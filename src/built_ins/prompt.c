/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** prompt
*/

#include "definition.h"
#include "exec.h"
#include "built_ins.h"
#include "common.h"

int my_tablen(char **tab);

static const char *help = "USAGE : prompt [prompt string]\n\t"\
                        "You can write different variables in your prompt :"\
                        "\n\t-GIT Branch (@GIT)\n\t-User name (@USER)\n\t"
                        "-Current dir (@PWD)\n"\
                        "The prompt is compatible with Env. vars aswell.\n"\
                        "Ex : @USER will dynamically show you the $USER, "\
                        "even if it changes. $USER will show you the $USER"\
                        " value at command time.\n"\
                        "Use the quote \"to use ><&|; type\"\n"\
                        "Exemple: prompt \"@USER> \"";

void set_prompt(char **tab, head_t *head)
{
    CLEAR(full_tab) char **new_tab = calloc(4, sizeof(char *));
    char *ref[] = {"setenv", "PROMPT", tab[1], NULL};
    char *eh = (tab[1] == NULL ? "few" : "many");

    if (return_value((tab[1] == NULL || tab[2] != NULL)))
        return (void)dprintf(2, "prompt: Too %s arguments.\n", eh);
    if (strcmp("-h", tab[1]) == 0)
        return (void)dprintf(1, "%s\n", help);
    for (int i = 0; i < 4; i++)
        new_tab[i] = (ref[i] != NULL ? strdup(ref[i]) : NULL);
    my_setenv(new_tab, head);
}