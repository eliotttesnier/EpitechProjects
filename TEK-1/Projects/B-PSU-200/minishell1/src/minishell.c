/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell
*/

#include "../includes/header.h"

static int perm_denied(char *binary)
{
    char *str = my_strcat(my_strcat(binary, ":"), " Permission denied.\n");

    write(2, str, my_strlen(str));
    return (1);
}

static int command_not_found(char *binary)
{
    char *str = my_strcat(my_strcat(binary, ":"), " Command not found.\n");

    write(2, str, my_strlen(str));
    return (1);
}

static int have_perm(char *path)
{
    if (access(path, F_OK) != 0)
        return (0);
    if (access(path, X_OK) != 0)
        return (1);
    return (0);
}

static int is_dir(char *path)
{
    struct stat sb;

    stat(path, &sb);
    return (S_ISDIR(sb.st_mode));
}

static int crash(int wstatus)
{
    if (wstatus == 11)
        write(2, "Segmentation fault\n", 19);
    else
        write(2, "Segmentation fault (core dumped)\n", 34);
    return (139);
}

int failed_exec(char *binary)
{
    if (errno == 2)
        return (command_not_found(binary));
    return (0);
}

int exec_path(char *binary, char **args, env_t *env)
{
    int wstatus = 0;
    pid_t child;
    pid_t parent;

    if (is_dir(binary) == 1 || have_perm(binary) == 1)
        return (perm_denied(binary));
    child = fork();
    if (child == 0) {
        execve(binary, args, env->env);
        exit(EXIT_FAILURE);
    }
    parent = waitpid(child, &wstatus, WUNTRACED | WCONTINUED);
    if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
        return (failed_exec(binary));
    if (wstatus == 139 || wstatus == 11)
        return (crash(wstatus));
    return (WEXITSTATUS(wstatus));
}

int find_path(char *binary, char **args, env_t *env)
{
    char *entire;
    char **paths = NULL;

    for (int i = 0; env->env[i] != NULL; i++) {
        if (my_strccmp("PATH", env->env[i], '=') == 0)
            paths = str_to_array(env->env[i]);
    }
    for (int i = 1; paths[i] != NULL; i++) {
        if (access(my_strcat(my_strcat(paths[i], "/"), binary), F_OK) == 0) {
            entire = my_strcat(my_strcat(paths[i], "/"), binary);
            return (exec_path(entire, args, env));
        }
    }
    return (command_not_found(binary));
}

int execute_command(char **com, env_t *env)
{
    for (int i = 0; com[0][i] != '\0'; i++) {
        if (com[0][i] == '/')
            return (exec_path(com[0], com, env));
    }
    return (find_path(com[0], com, env));
}
