#include "shell.h"
void exec_fg_bg_kjob(char *str, char **args)
{
    int fg = (strcmp(str, "fg") == 0) ? 1 : 0;
    int bg = (strcmp(str, "bg") == 0) ? 1 : 0;
    int kjob = (strcmp(str, "kjob") == 0) ? 1 : 0;
    if (args[1] == NULL || args[1][0] == '\0')
    {
        write(1, "Invalid usage! \n", 17);
        return;
    }
    if (!kjob && args[2] != NULL && args[2][0] != '\0')
    {
        write(1, "Invalid usage! \n", 17);
        return;
    }
    if (kjob && ((args[2] == NULL || args[2][0] == '\0') || (args[3] != NULL && args[3][0] != '\0')))
    {
        write(1, "Invalid usage! \n", 17);
        return;
    }
    int job_no = atoi(args[1]), c = 0, sig_no, st;
    if (kjob)
        sig_no = atoi(args[2]);
    for (int i = 0; i < jobs_size; i++)
    {
        if (all_jobs[i].type != 0)
        {
            if (!(++c - job_no))
            {
                kill(all_jobs[i].pid, kjob ? sig_no : SIGCONT);
                char *st;
                all_jobs[i].type = get_status(all_jobs[i].pid);
                if (fg)
                {
                    cur_fg = all_jobs[i];
                    cur_fg.type = FG;
                    int sct;
                    all_jobs[i].type = 0;
                    while (waitpid(cur_fg.pid, &sct, WNOHANG) != cur_fg.pid)
                    {
                        if (ctrc == 1)
                        {
                            ctrc = 0;
                            cur_fg.type = 0;
                            signal(SIGINT, sigintHandler);
                            kill(cur_fg.pid, SIGKILL);
                            break;
                        }
                        if (ctrz == 1)
                        {
                            cur_fg.type = 0;
                            ctrz = 0;
                            signal(SIGTSTP, sigtstpHandler);
                            char buffer[4096];
                            if (help == 0)
                            {
                                kill(cur_fg.pid, SIGSTOP);
                                sprintf(buffer, "Process %s with id %d has been stopped (calling from fg)\n", cur_fg.name, cur_fg.pid);
                                write(1, buffer, strlen(buffer));
                                all_jobs[jobs_size] = cur_fg;
                                all_jobs[jobs_size++].type = STP;
                                help = 1;
                            }
                            break;
                        }
                    }
                    all_jobs[i].pid = -1;
                }
                return;
            }
        }
    }
    write(1, "Error: job number does not exist\n", 34);
    return;
}