#include <stdio.h>
#define TAB '\t'
#define MAXLEN 1000
#define TAB_SIZE 5

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}

void detab(char line[], int length)
{
    char temp[MAXLEN];
    int c;
    int i = 0;
    int j = 0;
    while (line[i] != '\0') {
        if (line[i] != TAB) {
            temp[j] = line[i];
            j++;
        } else {
            int space_num = TAB_SIZE-(j%TAB_SIZE);
            for (; space_num > 0; space_num--){
                temp[j++] = ' ';
            }
        }
        i++;
    }
    temp[j] = '\0';
    copy(line, temp);
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

int main()
{
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0){
        detab(line, len);
        printf("%s", line);
    }
}