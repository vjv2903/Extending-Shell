#include "shell.h"
void exec_ls(char *arg, char **args)
{
    char *current_dir = NULL;
    struct dirent **namelist;
    int l = 0, a = 0;
    for (int i = 1; args[i] != NULL && args[i][0] != '\0'; ++i)
    {
        if (strcmp(args[i], "-la") == 0)
            l = a = 1;
        else if (strcmp(args[i], "-al") == 0)
            l = a = 1;
        else if (strcmp(args[i], "-l") == 0)
            l = 1;
        else if (strcmp(args[i], "-a") == 0)
            a = 1;
        else if (current_dir == NULL && strcmp(args[i], "&") != 0)
            current_dir = args[i];
        else if (strcmp(args[i], "&") != 0)
        {
            write(1, "Invalid usage: Invalid arguments\n", 49);
            return;
        }
    }
    current_dir = (current_dir == NULL) ? "." : current_dir;
    if (current_dir[0] == '~')
    {
        if (strcmp(current_dir, "~") == 0)
            strcpy(current_dir, home);
        else
        {
            char path[1024];
            strcpy(path, home);
            strcat(path, "/");
            strcat(path, args[1] + 2);
            strcpy(current_dir, path);
        }
    }
    int n = scandir(current_dir, &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        while (n--)
        {
            int display = 0;
            if (a == 1)
                display = 1;
            else if (namelist[n]->d_name[0] != '.')
                display = 1;
            if (display)
            {
                if (l == 0)
                {
                    write(1, namelist[n]->d_name, strlen(namelist[n]->d_name));
                    write(1, "\n", 2);
                }
                else
                {
                    char *file_path = (char *)malloc(sizeof(char) * 1024);
                    file_path[0] = '\0';
                    file_path = strcat(file_path, current_dir);
                    file_path = strcat(file_path, "/");
                    file_path = strcat(file_path, namelist[n]->d_name);
                    struct stat file_status;
                    if (stat(file_path, &file_status) != 0)
                    {
                        perror("Reading done wrong");
                        return;
                    }
                    char perm_str[20], buffer[4096], date[16];
                    int i = 0;
                    if (S_ISREG(file_status.st_mode))
                        perm_str[i++] = '-';
                    else if (S_ISDIR(file_status.st_mode))
                        perm_str[i++] = 'd';
                    else if (S_ISCHR(file_status.st_mode))
                        perm_str[i++] = 'c';
                    else if (S_ISBLK(file_status.st_mode))
                        perm_str[i++] = 'b';
                    else if (S_ISFIFO(file_status.st_mode))
                        perm_str[i++] = 'f';
                    else if (S_ISLNK(file_status.st_mode))
                        perm_str[i++] = 'l';
                    else
                        perm_str[i++] = 's';
                    if (file_status.st_mode & S_IRUSR)
                        perm_str[i++] = 'r';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IWUSR)
                        perm_str[i++] = 'w';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IXUSR)
                        perm_str[i++] = 'x';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IRGRP)
                        perm_str[i++] = 'r';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IWGRP)
                        perm_str[i++] = 'w';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IXGRP)
                        perm_str[i++] = 'x';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IROTH)
                        perm_str[i++] = 'r';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IWOTH)
                        perm_str[i++] = 'w';
                    else
                        perm_str[i++] = '-';
                    if (file_status.st_mode & S_IXOTH)
                        perm_str[i++] = 'x';
                    else
                        perm_str[i++] = '-';
                    perm_str[i++] = ' ';
                    perm_str[i++] = '\0';
                    struct passwd *pw = getpwuid(file_status.st_uid);
                    struct group *gr = getgrgid(file_status.st_gid);
                    if (pw == 0 || gr == 0)
                    {
                        perror("Error : User or group not found");
                        return;
                    }
                    strftime(date, 16, "%b %2d %2I:%2M", gmtime(&(file_status.st_mtime)));
                    sprintf(buffer, "%s %2zu %s %s %7zu %s %s\n", perm_str, file_status.st_nlink, pw->pw_name, gr->gr_name, file_status.st_size, date, namelist[n]->d_name);
                    write(1, buffer, strlen(buffer));
                    free(file_path);
                }
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    fflush(stdout);
}
