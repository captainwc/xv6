#include "user/sk.h"

#define PRINT_ERROR_POSITION 1

// ----------------------- util --------------------------

// copy bytes between [vstart, vend] to vdst
void copyrange(void *vdst, const void *vstart, const void *vend)
{
    const char *start = vstart;
    const char *end = vend;
    char *dst = vdst;

    while (start <= end)
    {
        memcpy(dst++, start++, 1);
    }
}

// free every pointer in p
void free_arr(void **p, int num)
{
    for (int i = 0; i < num; i++)
    {
        free(p[i]);
    }
}

// --------------------- string util ----------------------------

// return num of the splited str
int split(char *ret[], char *str, char sep)
{
    char *start = str;
    char *end = str;
    int count = 0;

    while (*end != '\0')
    {
        if (*end == ' ')
        {
            *end = '\0';
            ret[count] = start;
            count++;
            start = end + 1;
        }
        end++;
    }
    ret[count++] = start;
    ret[count + 1] = 0;
    return count;
}

// read line from fd
// 0 -> EOF, n -> line length, negtive -> error
int getline(int fd, char *buf, const int line_size)
{
    char ch;
    int rret;
    for (int i = 0; (rret = READ(fd, &ch, 1)) == 1; i++)
    {
        if (i >= line_size - 1)
        {
            return -2;
        }
        buf[i] = ch;
        if (ch == '\n')
        {
            buf[i] = 0;
            return i;
        }
    }
    return rret;
}

// return base_name's start pos to origin path
const char *base_name(const char *path)
{
    const char *p;
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;
    // int len = strlen(p);
    // char *ret = (char *)malloc(len);
    // memcpy(ret, p, len);
    return p;
}

// is str begin with substr yes -> 1 AND no -> 0
int begin_with(const char *str, const char *substr)
{
    while (*str != 0 && *substr != 0)
    {
        if (*str == *substr)
        {
            str++;
            substr++;
        }
        else
        {
            return 0;
        }
    }
    return *substr == 0;
}

// first position substr appeared in str, no -> NULL AND yes -> start pos
const char *strstr(const char *str, const char *substr)
{
    const char *pos = str;
    while (*pos != 0)
    {
        if (begin_with(pos, substr))
        {
            return pos;
        }
        pos++;
    }
    return (const char *)0;
}

// debug
void sk_perror(const char *file, const char *func, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
#if PRINT_ERROR_POSITION
    fprintf(2, "[%s, %s, %d][ERROR] ", file, func, line);
#endif
    vprintf(2, fmt, ap);
}

void sk_log(const char *file, const char *func, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
#if PRINT_ERROR_POSITION
    fprintf(1, "[%s, %s, %d][DEBUG] ", file, func, line);
#endif
    vprintf(1, fmt, ap);
}

// checked system call
int open_checked(const char *file, const char *func, int line, const char *openfile, int mode)
{
    int ret = open(openfile, mode);
    if (ret < 0)
    {
        sk_perror(file, func, line, "failed open file: %s\n", openfile);
    }
    return ret;
}

int fstat_checked(const char *file, const char *func, int line, int fd, struct stat *st)
{
    int ret = fstat(fd, st);
    if (ret < 0)
    {
        sk_perror(file, func, line, "cannot stat file: %d\n", fd);
    }
    return ret;
}

int read_checked(const char *file, const char *func, int line, int fd, void *buf, int num)
{
    int ret = read(fd, buf, num);
    if (ret < 0)
    {
        sk_perror(file, func, line, "read failed, fd: %d\n", fd);
    }
    return ret;
}

int write_checked(const char *file, const char *func, int line, int fd, const void *buf, int num)
{
    int ret = write(fd, buf, num);
    if (ret < 0)
    {
        sk_perror(file, func, line, "write failed, fd: %d\n", fd);
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

int fork_checked(const char *file, const char *func, int line)
{
    int pid = fork();
    if (pid == -1)
    {
        sk_perror(file, func, line, "fork failed\n");
    }
    return pid;
}