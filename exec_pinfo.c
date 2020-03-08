#include "shell.h"
void exec_pinfo(char *str, char **args)
{
    char *path, *spid, *buffer, *line, *ex_path;
    path = (char *)malloc(sizeof(char) * 1024);
    spid = (char *)malloc(sizeof(char) * 1024);
    buffer = (char *)malloc(sizeof(char) * 1024);
    line = (char *)malloc(sizeof(char) * 1024);
    ex_path = (char *)malloc(sizeof(char) * 1024);
    if (!path || !spid || !buffer || !line)
    {
        perror("Memory");
        return;
    }
    if (args[1] == NULL || args[1][0] == '\0' || strcmp(args[1], "&") == 0)
        sprintf(spid, "%d", (isbg) ? getppid() : getpid());
    else
        strcpy(spid, args[1]);
    sprintf(path, "/proc/%s/status", spid);
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        perror(path);
        return;
    }
    sprintf(buffer, "pid -- %s\n", spid);
    write(1, buffer, strlen(buffer));
    size_t sz = 0;
    int x = 0, y = 0;
    while (getline(&line, &sz, file) != -1)
    {
        if (x == 1 && y == 1)
            break;
        if (x == 0 && strncmp("State", line, 5) == 0)
        {
            write(1, "Process Status -- ", 19);
            int cur = 0;
            x = 1;
            for (int i = 7; line[i] != '\0'; i++)
                buffer[cur++] = line[i];
            buffer[cur] = '\0';
            write(1, buffer, strlen(buffer));
            x = 1;
        }
        else if (y == 0 && strncmp("VmSize", line, 6) == 0)
        {
            write(1, "memory -- ", 11);
            int cur = 0;
            y = 1;
            for (int i = 8; line[i] != '\0'; i++)
                buffer[cur++] = line[i];
            buffer[cur] = '\0';
            write(1, buffer, strlen(buffer));
            y = 1;
        }
    }
    fclose(file);
    sprintf(path, "/proc/%s/exe", spid);
    int s = readlink(path, line, 1024);
    write(1, "Executable path -- ", 20);
    if (s < 0)
    {
        perror("Error");
        return;
    }
    write(1, line, s);
    write(1, "\n", 2);
    free(spid);
    free(buffer);
    free(path);
    free(ex_path);
    free(line);
}