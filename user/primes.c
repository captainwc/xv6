#include "kernel/types.h"
#include "user/user.h"

const int END = 35;

void log(int x)
{
    fprintf(1, "prime %d\n", x);
}

void work(int start, int *fd)
{
    if (start > END || start == 0)
    {
        close(fd[0]);
        exit(0);
    }
    log(start);
    int fd2[2];
    pipe(fd2);
    int pid = fork();
    int int_buf = 0;
    if (pid > 0)
    {
        close(fd2[0]);
        while (read(fd[0], &int_buf, sizeof(int)) > 0)
        {
            if (int_buf % start != 0)
            {
                write(fd2[1], &int_buf, sizeof(int));
            }
        }
        close(fd[0]);
        close(fd2[1]);
        wait(0);
    }
    else
    {
        close(fd[0]);
        close(fd2[1]);
        read(fd2[0], &int_buf, sizeof(int));
        work(int_buf, fd2);
    }
    exit(0);
}

int main()
{
    int fd[2];
    pipe(fd);
    log(2);
    int pid = fork();
    if (pid > 0)
    {
        close(fd[0]);
        for (int i = 3; i <= END; i++)
        {
            if (i % 2 != 0)
            {
                write(fd[1], &i, sizeof(int));
            }
        }
        close(fd[1]);
        wait(0);
    }
    else
    {
        close(fd[1]);
        int int_buf = 0;
        read(fd[0], &int_buf, sizeof(int));
        work(int_buf, fd);
    }
    exit(0);
}