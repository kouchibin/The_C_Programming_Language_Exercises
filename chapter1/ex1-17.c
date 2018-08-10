#include <stdio.h>
#define MAXLEN 1000

int get_line(char line[], int limit);

int main()
{
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0){
        if (len > 80)
            printf("%s", line);
    }
}

int get_line(char line[], int limit)
{
    int c, i;
    for (i = 0; i < limit-1; ++i){
        c = getchar();
        if (c == '\n' || c == EOF){
            line[i] = '\n';
            line[i+1] = '\0';
            return i + 1;
        } else {
            line[i] = c;
        }
    }
    line[i] = '\0';
    return i;
}