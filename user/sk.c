#include "user/sk.h"

#define PRINT_ERROR_POSITION 1

// sk
void sk_perror(const char *file, const char *func, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
#if PRINT_ERROR_POSITION
    fprintf(2, "【%s, %s, %d】", file, func, line);
#endif
    vprintf(2, fmt, ap);
}

// checked system call
int open_checked(const char *file, const char *func, int line, const char *openfile, int mode)
{
    int ret = open(openfile, mode);
    if (ret < 0)
    {
        sk_perror(file, func, line, "failed open file: %s\n", file);
    }
    return ret;
}

int fstat_checked(const char *file, const char *func, int line, int fd, struct stat *st)
{
    int ret = fstat(fd, st);
    if (ret < 0)
    {
        sk_perror(file, func, line, "cannot stat file: %d\n", fd);
        close(fd);
    }
}

int read_checked(const char *file, const char *func, int line, int fd, void *buf, int num)
{
    int ret = read(fd, buf, num);
    if (ret < 0)
    {
        sk_perror(file, func, line, "read failed, fd: %d\n", fd);
        close(fd);
    }
    return ret;
}

int write_checked(const char *file, const char *func, int line, int fd, const void *buf, int num)
{
    int ret = write(fd, buf, num);
    if (ret < 0)
    {
        sk_perror(file, func, line, "write failed, fd: %d\n", fd);
        close(fd);
    }
    return ret;
}

int pipe_checked(const char *file, const char *func, int line, int *fd)
{
    int ret = pipe(fd);
    if (ret < 0)
    {
        sk_perror(file, func, line, "pipe failed\n");
    }
    return ret;
}