/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-lucas.lhomme
** File description:
** my_trimspace
*/
#include <string.h>
#include "lib.h"
#include <ctype.h>

int my_isspace(char c)
{
    return (c == ' ' || c == '\t' ||
        c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *trim_whitespace(char *str)
{
    char *end;

    while (my_isspace(*str))
        str++;
    if (*str == 0)
        return str;
    end = str + my_strlen(str) - 1;
    while (end > str && my_isspace(*end))
        end--;
    *(end + 1) = '\0';
    return str;
}
