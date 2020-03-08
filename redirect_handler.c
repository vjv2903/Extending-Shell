#include "shell.h"
void redirect_handler(char **args)
{
    int fd = 0;
    for (int i = 0; args[i] != NULL && args[i][0] != '\0'; i++)
    {
        if (!(strcmp(args[i], "<")))
        {
            fd = open(args[i + 1], O_RDONLY, 0);
            if (fd < 0)
            {
                perror("File");
                exit(1);
            }
            dup2(fd, 0);
            close(fd);
        }
        else if (!strcmp(args[i], ">"))
        {
            fd = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd < 0)
            {
                perror("File");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }
        else if (!strcmp(args[i], ">>"))
        {
            fd = open(args[i + 1], O_APPEND | O_RDWR | O_CREAT, 0644);
            if (fd < 0)
            {
                perror("File");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }
        if (!strcmp(args[i], "<") || !strcmp(args[i], ">>") || !strcmp(args[i], ">"))
            args[i] = NULL;
    }
}