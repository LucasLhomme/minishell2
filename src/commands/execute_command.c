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

char *cleaning_buffer(char *str)
{
    char *end = str + my_strlen(str) - 1;

    for (; *str == ' ' || *str == '\t'; str++);
    for (; end > str && (*end == ' ' || *end == '\t'); end--)
        *end = '\0';
    return str;
}

int execute_bin(char *path, char **argv, char **env)
{
    int status = 0;

    if (fork() == 0)
        status = execve(path, argv, env);
    wait(&status);
    free(path);
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
    return WEXITSTATUS(status);
}
