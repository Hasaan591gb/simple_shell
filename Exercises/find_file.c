#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    struct stat st;
    char *path, *token, *fullpath;
    int i;

    if (argc < 2)
    {
        printf("Usage: %s filename ...\n", argv[0]);
        return (1);
    }

    path = getenv("PATH");
    if (!path)
    {
        fprintf(stderr, "Error: PATH environment variable not set\n");
        return (1);
    }

    i = 1;
    while (argv[i])
    {
        printf("%s:", argv[i]);
        token = strtok(path, ":");
        while (token)
        {
            fullpath = malloc(strlen(token) + strlen(argv[i]) + 2);
            sprintf(fullpath, "%s/%s", token, argv[i]);
            if (stat(fullpath, &st) == 0)
            {
                printf(" FOUND\n");
                free(fullpath);
                break;
            }
            free(fullpath);
            token = strtok(NULL, ":");
        }
        if (!token)
            printf(" NOT FOUND\n");
        i++;
    }

    return (0);
}
