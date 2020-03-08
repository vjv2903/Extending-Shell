#include "shell.h"
void exec_jobs(char *arg, char **args)
{
    int c = 0;
    char *buffer = (char *)malloc(4096);
    if (args[1] != NULL && args[1][0] != '\0')
        write(1, "jobs: too many arguments\n", 26);
    else
    {
        for (int i = 0; i < jobs_size; i++)
        {
            all_jobs[i].type = get_status(all_jobs[i].pid);
            if (all_jobs[i].type)
            {
                sprintf(buffer, " [%d] %s %s [%d]\n", ++c, (all_jobs[i].type == BG) ? "Running" : "Stopped", all_jobs[i].name, all_jobs[i].pid);
                write(1, buffer, strlen(buffer));
            }
        }
    }
    free(buffer);
}
