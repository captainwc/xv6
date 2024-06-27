#include "kernel/types.h"
#include "user/user.h"

int sk_atoi(const char *str)
{
    int i = 0;
    while (*str >= '0' && *str <= '9')
    {
        i = i * 10 + *str++ - '0';
    }
    return i;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(2, "Bad boy, you should sleep good.\n");
        exit(-1);
    }
    int ret = sk_atoi(argv[1]);
    fprintf(1, "ready to sleep for %d seconds...\n", ret);
    sleep(ret);
    exit(0);
}