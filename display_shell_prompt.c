#include "shell.h"
char *display_shell_prompt()
{
    char username[1024], system_name[1024], current_directory[1024], directory[1024];
    gethostname(system_name, 1024);
    getlogin_r(username, 1024);
    getcwd(current_directory, 1024);
    if (strncmp(current_directory, home, strlen(home)) == 0)
    {
        directory[0] = '~';
        int i = 1, j = strlen(home);
        while (current_directory[j] != '\0')
            directory[i++] = current_directory[j++];
        directory[i] = '\0';
    }
    else
        strcpy(directory, current_directory);
    char *buffer = (char *)malloc(sizeof(char) * 3200);
    buffer[0] = '\0';
    strcat(buffer, "\033[0m<\033[0;32m");
    strcat(buffer, username);
    strcat(buffer, "\033[0m@\033[0;32m");
    strcat(buffer, system_name);
    strcat(buffer, ":\033[0m\033[0;34m");
    strcat(buffer, directory);
    strcat(buffer, "\033[0m>");
    return buffer;
}
