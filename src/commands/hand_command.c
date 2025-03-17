/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** hand_command
*/
#include "lib.h"
#include "my.h"

int hand_command(char *buffer, char **env)
{
    int i = 0;

    cleaning_buffer(buffer);
    if (my_strncmp(buffer, "cd", 2) == 0)
        return my_cd(buffer, env);
    if (my_strncmp(buffer, "setenv", 6) == 0 ||
    my_strncmp(buffer, "unsetenv", 8) == 0 ||
    my_strncmp(buffer, "env", 3) == 0)
        return my_env(buffer, env);
    else {
        while (buffer[i] == ' ' || buffer[i] == '\t')
            i++;
        if (buffer[i] != '\0')
            return searching_bin(buffer, env);
    }
    return 0;
}
