#include "user/sk.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

// match -> contains
int name_match(const char *name, const char *pattern)
{
    if (pattern == 0)
    {
        return 1;
    }
    if (strstr(name, pattern) != 0)
    {
        return 1;
    }
    return 0;
}

// only match filename, dirname matches is ignore.
void find(char *path, const char *pattern)
{
    char buf[512], *p;
    struct dirent de;
    struct stat st;
    int fd = OPEN(path, 0);
    if (fd < 0)
        return;
    if (FSTAT(fd, &st) < 0)
    {
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        if (name_match(base_name(path), pattern))
        {
            fprintf(1, "%s\n", path);
        }
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            PERROR("path too long: %s/%s\n", path, de.name);
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (READ(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            {
                continue;
            }
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf, pattern);
        }
        break;
    default:
        break;
    }
    close(fd);
}

// find [path] [pattern];
// if no args given, find with list all files in "." recursivly
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        find(".", 0);
    }
    else if (argc == 2)
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