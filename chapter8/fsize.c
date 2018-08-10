#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "dirent.h"

void fsize(char *);

int main(int argc, char **argv)
{
    errno = 0;
    if (argc == 1)
        fsize(".");
    else 
        while (--argc > 0)
            fsize(*++argv);
    if (errno != 0) {
        printf("err:%d\n", errno);
    }
    return 0;
}

int state(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    DIR *dfd;
    Dirent *dp;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0
         || strcmp(dp->name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n",
                dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

int fstat(int fd, struct stat *);

// DIR *opendir(char *dirname)
// {
//     int fd;
//     struct stat stbuf;
//     DIR *dp;

//     if ((fd = open(dirname, O_RDONLY, 0)) == -1
//      || fstat(fd, &stbuf) == -1
//      || (stbuf.st_mode & S_IFMT) != S_IFDIR
//      || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
//         return NULL;
//     dp->fd = fd;
//     return dp;
// }

void closedir(DIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

#ifndef DIRSIZ
#define DIRSIZ 14
#endif
struct direct
{
    ino_t d_ino;
    char d_name[DIRSIZ];
};

