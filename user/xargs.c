#include "user/sk.h"

void append(char *ret[], char *added[], int retend)
{
    for (int i = 0; added[i]; i++)
    {
        ret[retend++] = added[i];
    }
    ret[retend] = 0;
}

int main(int argc, char **argv)
{
    const int BUFF_SIZE = 100;
    char buf[BUFF_SIZE];
    if (argc == 1)
    {
        int i = 1;
        while (getline(0, buf, BUFF_SIZE) > 0)
        {
            fprintf(1, "%d:%s\n", i++, buf);
        }
    }
    else
    {
        char *cmd = *(argv + 1);
        char *cmdargs[BUFF_SIZE];
        int i = 0;
        for (; i < argc - 1; i++)
        {
            cmdargs[i] = argv[i + 1];
        }
        int linelen;
        while ((linelen = getline(0, buf, BUFF_SIZE)) > 0)
        {
            char *splitargs[BUFF_SIZE];
            split(splitargs, buf, ' ');
            append(cmdargs, splitargs, i);
            int pid = FORK();
            if (pid == 0)
            {
                exec(cmd, cmdargs);
            }
            else
            {
                wait(0);
            }
        }
    }
    exit(0);
}