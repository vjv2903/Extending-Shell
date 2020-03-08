#include "shell.h"
void exec_env(char *str, char **args)
{
    int set = (strcmp(str, "setenv") == 0) ? 1 : 0;
    int unset = (strcmp(str, "unsetenv") == 0) ? 1 : 0;
    if (args[1] == NULL || args[1][0] == '\0')
        write(1, "Invalid usage: Too few arguments\n", 34);
    else if (args[2] == NULL || args[2][0] == '\0')
    {
        if (set && setenv(args[1], "", 1) != 0)
            perror("cannot set variable");
        else if (unset && unsetenv(args[1]) != 0)
            perror("cannot unset variable");
    }
    else if (args[3] == NULL || args[3][0] == '\0')
    {
        if (set && setenv(args[1], args[2], 1) != 0)
            perror("cannot set variable");
        else if (unset)
            write(1, "Invalid usage: Too many arguments\n", 35);
    }
    else
        write(1, "Invalid usage: Too many arguments\n", 35);
}