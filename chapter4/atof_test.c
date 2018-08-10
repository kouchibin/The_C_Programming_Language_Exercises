#include <stdio.h>

#define MAXLINE 100
int get_line(char line[], int max);
double atof2(char []);

int main()
{
    printf("%d\n", '\0');
    double sum;
    char line[MAXLINE];
    sum = 0;
    while (get_line(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof2(line));
    return 0;
}

int get_line(char line[], int max)
{
    int i, c;
    for (i = 0; i < max-1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n'){
         line[i] == c;
         i++;
    }
    line[i] = '\0';
    return i;
}

