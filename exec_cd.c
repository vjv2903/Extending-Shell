#include "shell.h"
void exec_cd(char *arg, char **args)
{
    if (args[1] == NULL || args[1][0] == '\0')
        chdir(home);
    else if (args[2] != NULL && args[2][0] != '\0')
        write(1, "cd: invalid usage\n", 19);
    else if (strcmp(args[1], ".") == 0)
        return;
    else if (args[1][0] == '~')
    {
        if (strcmp(args[1], "~") == 0)
            chdir(home);
        else
        {
            char path[1024];
            strcpy(path, home);
            strcat(path, "/");
            strcat(path, args[1] + 2);
            if (chdir(path) < 0)
                perror("Error");
        }
    }
    else if (args[1][0] == '/' && chdir(args[1]) < 0)
        perror("Error");
    else if (chdir(args[1]) < 0)
        perror("Error");
}