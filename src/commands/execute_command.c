/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** execute command
*/
#include "my.h"
#include "lib.h"

int isalphanum_with_blanck(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (my_strcmp(buffer, " ") == 0 || my_strcmp(buffer, "\t") == 0
        || isalphanum(buffer[i]) == 0)
            return 1;
    }
    return 0;
}

char *cleaning_buffer(char *buffer)
{
    char *path = buffer;

    if (path == NULL)
        return NULL;
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '\n')
            path[i] = '\0';
    }
    return path;
}

int execute_bin(char *path, char **argv, char **env)
{
    int status = 0;

    if (fork() == 0) {
        execve(path, argv, env);
        exit(1);
    }
    wait(&status);
    free(path);
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
    return WEXITSTATUS(status);
}
