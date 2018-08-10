#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "fopen.h"
#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name,PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;
    if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else 
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int bufsize, num_written;
    if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;

    if (fp->base == NULL && (fp->flag & _UNBUF) == 0) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            fp->flag |= _UNBUF;
        else {
            fp->cnt = BUFSIZ - 1;
            fp->ptr = fp->base;
        }
    }

    if ((fp->flag & _UNBUF)) {
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
        if (c == EOF)
            return EOF;
        num_written = write(fp->fd, &c, 1);
        bufsize = 1;
    } else {
        if (c != EOF)
            *fp->ptr++ = c;
        bufsize = fp->ptr - fp->base;
        num_written = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ-1;
    }
    if (num_written == bufsize)
        return c;
    else {
        fp->flag |= _ERR;
        return EOF;
    }
    
}

int fflush(FILE *fp)
{
    int retval;
    if (fp == NULL) {
        for (int i = 0; i < OPEN_MAX; i++) {
            if ((_iob[i].flag & _WRITE) && (fflush(&_iob[i]) == -1))
                retval = -1;
        }
    } else {
        if ((fp->flag & _WRITE) == 0)
            return -1;
        _flushbuf(EOF, fp);
        if (fp->flag & _ERR)
            retval = -1;
    }
    return retval;
}

int fclose(FILE *fp)
{
    int d = fp->fd;
    if (fp == NULL) return EOF;
    fflush(fp);
    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL)
        free(fp->base);
    fp->base = NULL;
    fp->flag = 0;
    fp->fd = -1;
    return close(d);
}

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 }, 
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int fseek(FILE *fp, long offset, int origin)
{
    if (fp == NULL || (fp->flag & _ERR))
        return -1;
    int retval;
    if (((fp->flag & _UNBUF) == 0) && fp->base) {
        //deal with buffer
        if (fp->flag & _WRITE) 
            if (fflush(fp) == -1)
                return -1;
        else if (fp->flag & _READ) {
            if (origin == SEEK_CUR) {
                if (offset >= 0 && offset <= fp->cnt) {
                    fp->cnt -= offset;
                    fp->ptr += offset;
                    fp->flag &= ~_EOF;
                    return 0;
                } else {
                    offset -= fp->cnt;
                }
            }
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
    }
    retval = lseek(fp->fd, (off_t)offset, origin);
    if (retval != -1) {
        fp->flag &= ~_EOF;
        return 0;
    }
        
    else 
        return retval;
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    stdout->flag |= _UNBUF;
    int c;
    if (fseek(fp, 5, SEEK_SET) != 0){
        exit(1);
        fclose(fp);
    }
    while ((c = getc(fp)) != EOF) 
        putc(c, stdout);
    fclose(fp);
}
