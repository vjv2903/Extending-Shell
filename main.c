#include "shell.h"
void sigtstpHandler(int sig_num)
{
    ctrz = 1;
    if (help == 0 && cur_fg.type == FG)
    {
        kill(cur_fg.pid, SIGSTOP);
        char buffer[4096];
        sprintf(buffer, "Process %s with id %d has been stopped\n", cur_fg.name, cur_fg.pid);
        write(1, buffer, strlen(buffer));
        all_jobs[jobs_size] = cur_fg;
        all_jobs[jobs_size++].type = STP;
        help = 1;
    }
    cur_fg.type = 0;
    signal(SIGTSTP, sigtstpHandler);
}
void sigintHandler(int sig_num)
{
    ctrc = 1;
    if (!(cur_fg.type - FG))
    {
        cur_fg.type = 0;
        return;
    }
    signal(SIGINT, sigintHandler);
    fflush(stdout);
}
int main()
{
    shellPID = getpid();
    getcwd(home, 1024);
    signal(SIGINT, sigintHandler);
    jobs_size = 0;
    signal(SIGTSTP, sigtstpHandler);
    cur_fg.type = 0;
    char *buffer, *prompt;
    while (1)
    {
        int pid, status;
        ctrc = 0;
        ctrz = 0;
        help = 0;
        do
        {
            pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
            if (pid > 0 && (WIFEXITED(status) || WIFSIGNALED(status)))
            {
                for (int i = 0; i < jobs_size; i++)
                {
                    if (all_jobs[i].type && !(all_jobs[i].pid - pid))
                    {
                        char buffer[4096] = {0};
                        all_jobs[i].type = 0;
                        WIFEXITED(status)
                        ? sprintf(buffer, "%s with pid %d exited\nnormally with status %d\n", all_jobs[i].name, all_jobs[i].pid, WEXITSTATUS(status))
                        : sprintf(buffer, "%s with pid %d exited\nabnormally (terminated by a signal) with error status %d\n", all_jobs[i].name, all_jobs[i].pid, WEXITSTATUS(status));
                        write(1, buffer, strlen(buffer));
                    }
                }
            }
        } while (pid > 0);
        for (int i = 0; i < jobs_size; i++)
            all_jobs[i].type = get_status(all_jobs[i].pid);
        prompt = display_shell_prompt();
        buffer = readline(prompt);
        if (buffer == NULL)
        {
            write(1, "\n", 2);
            continue;
        }
        add_history(buffer);
        interpret_command(buffer, 0);
    }
    free(buffer);
}
