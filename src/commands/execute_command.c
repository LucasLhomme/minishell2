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
        if (my_strcmp(buffer, " ") == 0 || my_strcmp(buffer, "\t") == 0 || isalphanum(buffer[i]) == 0)
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

int searching_bin(char *buffer, char **env)
{
    char **argv = NULL;
    char *path = NULL;

    argv = my_str_to_word_array(buffer);
    path = malloc(my_strlen("/bin/") + my_strlen(argv[0]) + 1);
    if (!argv[0] || path == NULL)
        return 1;
    my_strcpy(path, "/bin/");
    my_strcat(path, argv[0]);
    cleaning_buffer(path);
    if (access(path, X_OK) == 0)
        return execute_bin(path, argv, env);
    else {
        my_printf("%s: Command not found.\n", argv[0]);
        free(path);
        for (int i = 0; argv[i] != NULL; i++)
            free(argv[i]);
        free(argv);
        return 1;
    }
}

int hand_command(char *buffer, char **env)
{
    cleaning_buffer(buffer);
    if (my_strncmp(buffer, "cd", 2) == 0)
        return my_cd(buffer, env);
    if (my_strncmp(buffer, "setenv", 6) == 0 ||
    my_strncmp(buffer, "unsetenv", 8) == 0 ||
    my_strncmp(buffer, "env", 3) == 0)
        return my_env(buffer, env);
    else {
        int i = 0;
        while (buffer[i] == ' ' || buffer[i] == '\t')
            i++;
        if (buffer[i] != '\0')
            return searching_bin(buffer, env);
    }
    return 0;
}
