#include "shell.h"
void interpret_command(char *cmd, int forcebg)
{
    char **cmds = string_splitter(cmd, ';', 0);
    int idkkkkk;
    for (int i = 0; cmds[i] != NULL && cmds[i][0] != '\0'; i++)
    {
        help = 0;
        char **args = string_splitter(cmds[i], ' ', 1);
        if (args[0] == NULL || args[0][0] == '\0')
            continue;
        if (isvalid_redirection(args) == 0)
            continue;
        if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0)
            exit(EXIT_SUCCESS);
        else if (strcmp(args[0], "cd") == 0)
            exec_cd(args[0], args);
        else if (strcmp(args[0], "overkill") == 0)
        {
            if (args[1] != NULL && args[1][0] != '\0')
                write(1, "overkill: too many arguments\n", 30);
            else
            {
                for (int i = 0; i < jobs_size; i++)
                {
                    if (all_jobs[i].type == BG)
                    {
                        kill(all_jobs[i].pid, 9);
                        all_jobs[i].type = 0;
                    }
                }
            }
        }
        else if (strcmp(args[0], "fg") == 0 || strcmp(args[0], "bg") == 0 || strcmp(args[0], "kjob") == 0)
            exec_fg_bg_kjob(args[0], args);
        else if (strcmp(args[0], "setenv") == 0 || strcmp(args[0], "unsetenv") == 0)
            exec_env(args[0], args);
        else
        {
            if (pipe_handler(cmds[i]) != -1)
                continue;
            if (forcebg == 1)
                isbg = 1;
            else
            {
                isbg = 0;
                int i = 0;
                for (; args[i][0] != '\0'; i++)
                    ;
                if (strcmp(args[i - 1], "&") == 0)
                {
                    args[i - 1] = NULL;
                    isbg = 1;
                }
                args[i] = NULL;
            }
            int pid = fork();
            if (pid == 0)
            {
                if (isbg)
                    setpgid(0, 0);
                redirect_handler(args);
                if (strcmp(args[0], "echo") == 0)
                {
                    for (int i = 1; args[i] != NULL && args[i][0] != '\0'; i++)
                    {
                        write(1, args[i], strlen(args[i]));
                        write(1, " ", 2);
                    }
                    write(1, "\n", 2);
                }
                else if (strcmp(args[0], "pwd") == 0)
                {
                    if (args[1] != NULL && args[1][0] != '\0')
                        write(1, "pwd: too many arguments\n", 25);
                    else
                    {
                        char *buffer = (char *)malloc((1024) * sizeof(char));
                        if (!buffer)
                        {
                            perror("Memory");
                            exit(1);
                        }
                        getcwd(buffer, 1024);
                        write(1, buffer, strlen(buffer));
                        write(1, "\n", 2);
                        free(buffer);
                    }
                }
                else if (strcmp(args[0], "ls") == 0)
                    exec_ls(args[0], args);
                else if (strcmp(args[0], "pinfo") == 0)
                    exec_pinfo(args[0], args);
                else if (strcmp(args[0], "jobs") == 0)
                    exec_jobs(args[0], args);
                else if (strcmp(args[0], "cronjob") == 0)
                    exec_cronjob(args[0], args);
                else
                {
                    int k = execvp(args[0], args);
                    if (k < 0)
                        perror("No command found");
                }
                fflush(stdout);
                exit(0);
            }
            else
            {
                if (isbg == 0)
                {
                    strcpy(cur_fg.name, args[0]);
                    cur_fg.pid = pid;
                    cur_fg.type = FG;
                    waitpid(pid, &idkkkkk, WUNTRACED);
                    cur_fg.type = 0;
                }
                else
                {
                    all_jobs[jobs_size].pid = pid;
                    strcpy(all_jobs[jobs_size].name, args[0]);
                    all_jobs[jobs_size].type = BG;
                    jobs_size++;
                }
            }
        }
        free(args);
    }
    free(cmds);
}