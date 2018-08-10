#include <stdio.h>
#define MAXLEN 1000

int get_line(char line[], int limit);

int main()
{
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0){
        if (len == 1)
            continue;
        int i = len - 2;
        while (i > 0 && (line[i] == '\t' || line[i] == ' '))
            i--;
        line[i + 1] = '\0';
        printf("%s\n", line);
    }
}

int get_line(char line[], int limit)
{
    int c, i;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n'){
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}