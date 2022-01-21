/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Common function header
*/

#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "magical_value.h"
#include "definition.h"

// String manipulation
char **my_str_to_array(char *str, char delim);
char **my_split(char *str, char const *delim);
int str_is_alpha_num(char *str, char *error);
int str_is_num(const char *str);
int my_tablen(char **tab);
char *my_strcat(char *s1, char *s2, bool f1, bool f2);
int my_tablen(char **tab);

// * The best function
void shift_str(char **str);
void shift_to_left(char *buffer, index_t shift);
void shift_to_right(char *buffer, index_t shift, char ch);

// * Theo concat function
char *my_strconcat_bsn(char *s1, char *s2);
char *my_strconcat_space(char *s1, char *s2);
void concate_args(head_t **head);
char *my_revstr(char *str);
char *my_itoa(int o);

char **kill_all_quotes(char **tab);

// * Useful define
#define IS_PAIR(x) x % 2 == 0
#define NOT_QUOTE(x) (x != '"' && x != '\'' && x != '`')

// * Cleanup
#define CLEAR(c) __attribute__((cleanup(clear_ ##c)))

void clear_str(char **p);
char *my_clean_str(char *str, char const *delim);
void clear_tab(char ***p);
void clear_full_tab(char ***p);
void free_list(cmd_t *list);
void free_alias(alias_t *alias);
void free_head(head_t *head);

#endif // COMMON_H
