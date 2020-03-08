#include "shell.h"
int get_status(int pid)
{
    char path[1024], ex_path[1024], spid[10];
    char *line;
    char s;
    size_t sz = 0;
    char *buffer = (char *)malloc(1024 * sizeof(char));
    if (!buffer)
    {
        perror("Memory");
        exit(1);
    }
    buffer[0] = '\0';
    sprintf(spid, "%d", pid);
    sprintf(path, "/proc/%s/status", spid);
    FILE *file = fopen(path, "r");
    if (file == NULL)
        return 0;
    while (getline(&line, &sz, file) != -1)
    {
        if (strncmp("State", line, 5) == 0)
        {
            int cur = 0;
            for (int i = 7; line[i] != '\0'; i++, cur++)
                buffer[cur] = line[i];
            buffer[cur] = '\0';
            fclose(file);
            free(line);
            if (buffer[0] == 'T')
                return STP;
            else if (buffer[0] == 'S' || buffer[0] == 'R')
                return BG;
            free(buffer);
            return BG - STP + 1 + BG;
        }
    }
}
