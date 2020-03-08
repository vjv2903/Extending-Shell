#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <math.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <stddef.h>
#include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
#define INV 0
#define FG 1
#define BG 2
#define STP 3
#ifndef SHELL_H
#define SHELL_H
char home[1024];
int isbg, shellPID, jobs_size, ctrz, ctrc, help;
struct ongoing_processes
{
    int pid;
    char name[1024];
    int type;
} cur_fg, all_jobs[2048];
void interpret_command(char *cmd, int forcebg);
int isvalid_redirection(char **args);
void sigtstpHandler(int sig_num);
void exec_cronjob(char *arg, char **args);
void sigintHandler(int sig_num);
void exec_pinfo(char *arg, char **args);
void exec_ls(char *arg, char **args);
char *display_shell_prompt();
void display_killed_children();
void exec_env(char *arg, char **args);
void redirect_handler(char **args);
int pipe_handler(char *cmd);
void exec_jobs(char *arg, char **args);
char **string_splitter(char *buffer, char sep, int redirection);
int get_status(int pid);
void exec_cd(char *arg, char **args);
void exec_fg_bg_kjob(char *arg, char **args);
#endif