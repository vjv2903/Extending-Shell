#include "shell.h"
int fildes[2];
int pipe_handler(char *cmd)
{
    char s;
    int no_of_pipes = 0, in_fd = dup(0), out_fd = dup(1);
    char **pipe_commands = string_splitter(cmd, '|', 0);
    while (pipe_commands[no_of_pipes] != NULL && pipe_commands[no_of_pipes][0] != '\0')
        no_of_pipes = no_of_pipes + 1;
    no_of_pipes = no_of_pipes - 1;
    if (no_of_pipes == 0)
        return -1;
    for (int i = 0, pid, status; i <= no_of_pipes; ++i)
    {
        if (i != no_of_pipes)
        {
            pipe(fildes);
            out_fd = dup(1);
            if (dup2(fildes[1], 1) == -1)
            {
                fprintf(stderr, "Error: dup2 failed\n");
                return 0;
            }
        }
        if (i)
        {
            close(fildes[1]);
            in_fd = dup(0);
            if (dup2(fildes[0], 0) == -1)
            {
                fprintf(stderr, "Error: dup2 failed\n");
                return 0;
            }
            close(fildes[0]);
        }
        pid = fork();
        if (!pid)
        {
            interpret_command(pipe_commands[i], 0);
            exit(0);
        }
        else
        {
            dup2(in_fd, 0);
            dup2(out_fd, 1);
            waitpid(pid, &status, WUNTRACED);
        }
    }
    return 0;
}