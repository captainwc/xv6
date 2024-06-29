#include "user/sk.h"

// you can add any function here
// and call them in "usertests"'s function "sktests()"
// Then you can use cmd "usertests" without args in xv6 shell to exectute all this functions.

void test_split()
{
    char **buf = 0;
    int num = split(buf, "hello, world, haha", ',');
    PERROR("Splited to %d\n", num);
    for (int i = 0; i < num; i++)
    {
        PERROR("%d:%s\n", i, *buf[i]);
    }
    free_arr((void **)buf, num);
}