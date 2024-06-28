#include "kernel/types.h"
#include "user/user.h"

int main()
{
    const int PIPE_READ = 0;
    const int PIPE_WRITE = 1;
    const int BUFF_SIZE = 5;
    int fd[2];
    if (pipe(fd) == -1)
    {
        fprintf(2, "pipe failed\n");
        exit(-1);
    }
    int pid = fork();
    char buff[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    if (pid == 0)
    {
        read(fd[PIPE_READ], buff, BUFF_SIZE);
        fprintf(1, "%d: received %s\n", getpid(), buff);
        close(fd[PIPE_READ]);
        write(fd[PIPE_WRITE], "pong", 4);
        close(fd[PIPE_WRITE]);
    }
    else
    {
        write(fd[PIPE_WRITE], "ping", 4);
        close(fd[PIPE_WRITE]);
        wait(0);
        read(fd[PIPE_READ], buff, BUFF_SIZE);
        close(fd[PIPE_READ]);
        fprintf(1, "%d: received %s\n", getpid(), buff);
    }
    exit(0); // 还不能用 return 呦
}