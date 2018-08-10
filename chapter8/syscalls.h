#include <stdio.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t count); 
int close(int fd);
ssize_t read(int fd, void *buf, size_t count); 
int open(const char *pathname, int flags); 
int open(const char *pathname, int flags, mode_t mode); 
int creat(const char *pathname, mode_t mode);