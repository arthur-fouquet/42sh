/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_exec_path.c
*/

#include "exec.h"
#include "common.h"

static const char *CMD_NOT_FOUND = ": Command not found.\n";
static const char *PERM_DENIED = ": Permission denied.\n";
extern char **environ;

static int check_perm(char *str)
{
    struct stat s;
    if (access(str, F_OK) != 0)
        return (1);
    lstat(str, &s);
    if (str[0] != '.' && str[0] != '/' && S_ISDIR(s.st_mode))
        return (1);
    if (access(str, X_OK) != 0)
        return (2);
    return (0);
}

int check_exec(char **env, char **str, char *error)
{
    int a = 0;
    int perm = 0;
    char *path = NULL;

    for (; env[a] != NULL; a++) {
        perm = check_perm(env[a]);
        if (perm == 0) {
            path = strdup(env[a]);
            break;
        }
    }
    if (path == NULL)
        dprintf(2, "%s%s", error, (perm == 1 ? CMD_NOT_FOUND : PERM_DENIED));
    free(*str);
    *str = path;
    return ((perm == 0 ? 0 : -1));
}

void malloc_concat_env(char **envi, char *str)
{
    for (int a = 0; envi[a] != NULL; a++) {
        envi[a] = strdup(envi[a]);
        envi[a] = realloc(envi[a], strlen(envi[a]) + strlen(str) + 2);
        envi[a] = strcat(strcat(envi[a], "/"), str);
    }
}

int is_binary(char *cmd)
{
    int perm = check_perm(cmd);

    if (cmd[0] == '.' && cmd[1] && cmd[1] == '/') {
        if (perm != 0)
            dprintf(2, "%s%s", cmd,
            (perm == 1 ? CMD_NOT_FOUND : PERM_DENIED));
        return (0);
    }
    if (perm == 0)
        return (0);
    return (-1);
}

int get_exec(char **str, char *cmd)
{
    char *path = getenv("PATH");
    char **envi = NULL;
    int ret = check_perm(cmd);

    if (is_binary(cmd) == 0) {
        (*str) = strdup(cmd);
        return (ret == 0 ? 0 : -1);
    }
    if (path == NULL || *path == '\0' || strcmp(path, "/") == 0) {
        dprintf(2, "%s: Command not found.\n", cmd);
        return (-1);
    } path = strdup(path);
    envi = my_str_to_array(path, ':');
    malloc_concat_env(envi, cmd);
    if (check_exec(envi, str, cmd) == -1)
        ret = -1;
    for (int a = 0; envi[a] != NULL; a++)
        free(envi[a]);
    free(envi);
    return (ret);
}
