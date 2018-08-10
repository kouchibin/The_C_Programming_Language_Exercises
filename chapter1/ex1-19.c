#include <stdio.h>
#define MAXLEN 1000

int get_line(char line[], int limit);
void reverse(char s[], int size);
void copy(char to[], char from[]);

int main()
{
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0){
        reverse(line, len);
        printf("%s", line);
    }
}

int get_line(char line[], int limit)
{
    int c, i;
    for (i=0; i<limit-1 && (c=getchar())!=EOF && c!='\n'; i++){
        line[i] = c;
    }
    if (c == '\n'){
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void reverse(char s[], int size)
{
    char temp[size];
    int i;
    for (i = 0; i < size - 1; i++){
        temp[i] = s[size - i - 2];
    }
    temp[i++] = '\n';
    temp[i] = '\0';
    copy(s, temp);
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}