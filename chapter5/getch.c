#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bp;

int getch(void)
{
    if (bp > 0)
        return buf[--bp];
    return getchar();
}

void ungetch(int c)
{
    if (bp == BUFSIZE)
        printf("error: buffer full.\n");
    else
        buf[bp++] = c;
}