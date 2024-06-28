#include "kernel/types.h"
#include "user/user.h"

void sk_perror(const char *file, const char *func, int line, const char *fmt, ...);
int open_checked(const char *file, const char *func, int line, const char *openfile, int mode);
int fstat_checked(const char *file, const char *func, int line, int fd, struct stat *st);
int read_checked(const char *file, const char *func, int line, int fd, void *buf, int num);
int write_checked(const char *file, const char *func, int line, int fd, const void *buf, int num);
int pipe_checked(const char *file, const char *func, int line, int *fd);

#define PERROR(msg, ...) sk_perror(__FILE__, __func__, __LINE__, msg, ##__VA_ARGS__)
#define OPEN(file, mode) open_checked(__FILE__, __func__, __LINE__, file, mode)
#define FSTAT(fd, st) fstat_checked(__FILE__, __func__, __LINE__, fd, st)
#define READ(fd, buf, size) read_checked(__FILE__, __func__, __LINE__, fd, buf, size)
#define WRITE(fd, buf, size) write_checked(__FILE__, __func__, __LINE__, fd, buf, size)
#define PIPE(fd) pipe_checked(__FILE__, __func__, __LINE__, fd)

#define TODO() sk_perror(__FILE__, __func__, __LINE__, "TODO!\n")

#define PANIC(msg)                                                    \
    do                                                                \
    {                                                                 \
        sk_perror(__FILE__, __func__, __LINE__, "[PAINC] %s\n", msg); \
        exit(-1);                                                     \
    } while (0)
