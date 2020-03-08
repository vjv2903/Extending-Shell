#include "shell.h"
int contains_redirection_or_piping(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == '>' || s[i] == '|' || s[i] == '<')
            return 1;
    return 0;
}
int isvalid_redirection(char **args)
{
    int i = 0;
    if (contains_redirection_or_piping(args[0]))
    {
        write(1, "Parse error near ", 18);
        write(1, args[0], strlen(args[0]));
        write(1, "\n", 2);
        return 0;
    }
    for (; args[i] != NULL && args[i][0] != '\0'; ++i)
    {
        if (contains_redirection_or_piping(args[i]) && !(strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], "|") == 0))
        {
            write(1, "Parse error near ", 18);
            write(1, args[i], strlen(args[i]));
            write(1, "\n", 2);
            return 0;
        }
    }
    if (contains_redirection_or_piping(args[i - 1]))
    {
        write(1, "Parse error near ", 18);
        write(1, args[i - 1], strlen(args[i - 1]));
        write(1, "\n", 2);
        return 0;
    }
    return 1;
}
