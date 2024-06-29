#include "user/sk.h"

// you can add any function here
// and call them in "usertests"'s function "sktests()"
// Then you can use cmd "usertests" without args in xv6 shell to exectute all this functions.

void test_split()
{
    LOG("[BEGIN]: split test\n");
    char str[] = "this is a test string";
    char *arr[100];
    int count = split(arr, str, ' ');

    for (int i = 0; i < count; i++)
    {
        printf("%s\n", arr[i]);
    }
    LOG("[END]: split test\n");
}

void test_exec()
{
    LOG("[BEGIN]: exec test\n");
    char *args[] = {"echo", "xx", 0};
    LOG("BEGIN exec\n");
    exec("echo", args);
    LOG("END exec");
}