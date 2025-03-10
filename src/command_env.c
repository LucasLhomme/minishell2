/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** command_env
*/
#include "my.h"
#include "lib.h"

int print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
    return 0;
}

int check_var(char *name)
{
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == '\0' || !my_isalpha(name[0])) {
            my_printf
            ("setenv: Variable name must begin with a letter.\n");
            return 1;
        }
        if (nonalphanum(name[i]) != 0) {
            my_printf
            ("setenv: Variable name must contain alphanumeric characters.\n");
            return 1;
        }
        if ((!my_isalpha(name[i]) && !my_isnum(name[i]))) {
            my_printf("setenv:");
            my_printf
            (" Variable name must contain only alphanumeric characters.\n");
            return 1;
        }
    }
    return 0;
}

int my_setenv(char *name, char *value, char **env)
{
    int exit_check_var = check_var(name);

    if (!name)
        return 84;
    if (exit_check_var != 0)
        return exit_check_var;
    if (value == NULL)
        return new_value_env(name, env);
    if (name != NULL || value != NULL)
        return over_value_env(name, value, env);
    return 0;
}

int my_env(char *buffer, char **env)
{
    char **argv = my_str_to_word_array(buffer);

    if (argv[2] == NULL)
        argv[2] = '\0';
    if (my_strncmp(buffer, "unsetenv", 8) == 0)
        return my_unsetenv(argv[1], env);
    if (my_strncmp(buffer, "env", 3) == 0)
        return print_env(env);
    if (my_strncmp(buffer, "setenv", 6) == 0) {
        if (argv[2] == NULL)
            return my_setenv(argv[1], NULL, env);
        if (argv[2] != NULL)
            return my_setenv(argv[1], argv[2], env);
    }
    return 0;
}
