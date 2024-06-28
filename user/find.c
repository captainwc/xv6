#include "user/sk.h"

void find(char *path, const char *pattern)
{
    PERROR("[path]: %s, [pattern]: %s\n", path, pattern);
}

// find [path] [pattern]
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        find(".", argv[1]);
    }
    else if (argc == 3)
    {
        find(argv[1], argv[2]);
    }
    else
    {
        PERROR("find: incorrect number of args\n");
        exit(-1);
    }
    exit(0);
}