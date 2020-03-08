#include "shell.h"
void exec_cronjob(char *arg, char **args)
{
    int is_flags_read[3] = {0, 0, 0}, p, t, cmd_length;
    char **cmd = (char **)malloc(1024 * sizeof(char *));
    char *cmd_str = (char *)malloc(sizeof(char) * 1024);
    if (!cmd_str || !cmd)
    {
        perror("Memory");
        exit(1);
    }
    for (int i = 1; args[i] != NULL && args[i][0] != '\0'; i=i+1)
    {
        if (strcmp(args[i], "-c") == 0 && is_flags_read[0] == 0)
        {
            i = i + 1;
            int cmd_length = 0;
            if (args[i] == NULL || args[i][0] == '\0')
            {
                write(1, "Erro: No command provided\n", 36);
                return;
            }
            for (; args[i] != NULL && args[i][0] != '\0' && strcmp(args[i], "-c") != 0 && strcmp(args[i], "-p") != 0 && strcmp(args[i], "-t") != 0; i=i+1)
            {
                cmd[cmd_length] = (char *)malloc(2048 * sizeof(char));
                if (!cmd[cmd_length])
                {
                    perror("Memory");
                    exit(1);
                }
                strcpy(cmd[cmd_length], args[i]);
                cmd_length++;
            }
            cmd[cmd_length++] = NULL;
            is_flags_read[0] = 1;
            cmd_str[0] = '\0';
            i = i - 1;
            for (int i = 0; cmd[i] != NULL && cmd[i][0] != '\0'; i=i+1)
            {
                strcat(cmd_str, cmd[i]);
                strcat(cmd_str, " ");
            }
        }
        else if (strcmp(args[i], "-t") == 0 && is_flags_read[1] == 0)
        {
            i = i + 1;
            if (args[i] == NULL || args[i][0] == '\0')
            {
                write(1, "Erro: No time provided\n", 33);
                return;
            }
            t = atoi(args[i]);
            if (t == 0)
            {
                write(1, "Erro: Invalid time\n", 29);
                return;
            }
            is_flags_read[1] = 1;
        }
        else if (strcmp(args[i], "-p") == 0 && is_flags_read[2] == 0)
        {
            i = i + 1;
            if (args[i] == NULL || args[i][0] == '\0')
            {
                write(1, "Erro: No period provided\n", 35);
                return;
            }
            p = atoi(args[i]);
            if (p == 0)
            {
                write(1, "Erro: Invalid period\n", 31);
                return;
            }
            is_flags_read[2] = 1;
        }
        else
        {
            write(1, "Erro: Invalid format\n", 31);
            return;
        }
    }
    if (is_flags_read[0] == 0 || is_flags_read[1] == 0 || is_flags_read[0] == 0)
    {
        write(1, "Erro: Invalid format\n", 31);
        return;
    }
    for (int i = 0; i < p / t; i=i+1)
    {
        interpret_command(cmd_str, 1);
        sleep(t);
    }
    sleep(p % t);
    free(cmd_str);
}