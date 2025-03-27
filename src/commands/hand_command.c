/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_command
*/
#include "lib.h"
#include "my.h"
#include <sys/stat.h>

const handle_command_t commands[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"setenv", my_setenv},
    {"unsetenv", my_env},
    {NULL, NULL}
};

int is_folder(char *buffer)
{
    struct stat path_stat;
    int exit_status = 0;

    if (stat(buffer, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
        my_printf("%s: Permission denied.\n", buffer);
        exit_status = 1;
    }
    return exit_status;
}

int my_execute_program(char *buffer, char **env)
{
    for (int i = 0; commands[i].command != NULL; i++) {
        if (my_strncmp(buffer, commands[i].command,
            my_strlen(commands[i].command)) == 0)
            return commands[i].func(buffer, env);
    }
    return searching_bin(buffer, env);
}

int hand_command(char *buffer, char **env)
{
    int exit_status = 0;

    trim_whitespace(buffer);
    if (is_folder(buffer) == 1)
        exit_status = 1;
    else
        exit_status = my_execute_program(buffer, env);
    return exit_status;
}
