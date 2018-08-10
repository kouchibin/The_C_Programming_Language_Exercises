#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFSIZ 1024

int main(int argc, char* argv[])
{
    int fd;
    int buf[BUFSIZ];
    if (argc == 1) {
        printf("Too little args.\n");
    }
    while (--argc > 0) {
        if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
            printf("Error occured when reading file: %s\n", *argv);
            exit(1);
        };
        int count;
        while ((count = read(fd, buf, BUFSIZ)) > 0) 
            if (write(1, buf, count) != count)
                fprintf(stderr, "write error\n");
        close(fd);
    }
}