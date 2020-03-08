#include "shell.h"
char **string_splitter(char *buffer, char sep, int redirection)
{
    char **result = (char **)malloc(1024 * sizeof(char *));
    if (!result)
    {
        perror("Memory");
        exit(1);
    }
    while (buffer[0] == sep)
        buffer++;
    while (buffer[strlen(buffer) - 1] == sep)
        buffer[strlen(buffer) - 1] = '\0';
    if (strcmp(buffer, "") == 0)
    {
        result[0] = (char *)malloc(2048 * sizeof(char));
        if (!result[0])
        {
            perror("Memory");
            exit(1);
        }
        result[0][0] = '\0';
        return result;
    }
    int rowno = 0;
    for (int i = 0; i < strlen(buffer); i = i + 1)
    {
        if (buffer[i] == ' ')
            continue;
        rowno = rowno + 1;
        result[--rowno] = (char *)malloc(2048 * sizeof(char));
        if (!result[rowno])
        {
            perror("Memory");
            exit(1);
        }
        int j = 0;
        while (buffer[i] != '\0' && buffer[i] != sep)
        {
            if (redirection == 1 && (buffer[i] == '>' || buffer[i] == '|' || buffer[i] == '<'))
            {
                if (j != 0)
                {
                    result[rowno][j] = '\0';
                    result[++rowno] = (char *)malloc(2048 * sizeof(char));
                    if (!result[rowno])
                    {
                        perror("Memory");
                        exit(1);
                    }
                    j = 0;
                }
                while (buffer[i] == '>' || buffer[i] == '|' || buffer[i] == '<')
                {
                    result[rowno][j] = buffer[i];
                    j++;
                    i++;
                }
                result[rowno][j] = '\0';
                rowno++;
                result[rowno] = (char *)malloc(2048 * sizeof(char));
                if (!result[rowno])
                {
                    perror("Memory");
                    exit(1);
                }
                j = 0;
            }
            else
                result[rowno][j++] = buffer[i++];
        }
        if (j != 0)
        {
            result[rowno][j] = '\0';
            rowno++;
        }
    }
    result[rowno] = (char *)malloc(2048 * sizeof(char));
    if (!result[rowno])
    {
        perror("Memory");
        exit(1);
    }
    result[rowno][0] = '\0';
    return result;
}
