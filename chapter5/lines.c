#include <stdio.h>
#define MAXLEN 100
int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line,MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char * lineptr[], int nlines)
{
    printf("\n");
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int get_line(char *to, int max)
{
    int c, i;
    for (i = 0; i < max && (c = getchar()) != '\n' && c != EOF; i++)
        to[i] = c;
    if (c == '\n')
        to[i++] = '\n';
    return i;
}