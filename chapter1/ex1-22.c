#include <stdio.h>
#define MAXLEN 1000
#define FOLD 10

int get_line(char line[], int limit);
void cut(char line[], int len);
void copy(char to[], char from[]);

char temp[MAXLEN];

int main()
{
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0) {
        cut(line, len);
        printf("%s", line);
    }
}

int get_line(char line[], int limit)
{
    int c, i;
    for (i = 0; i < limit -1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n'){
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void cut(char line[], int len)
{
    if (len <= FOLD) return;
    int buffer_index = 0;
    int col = 0;
    for (int i = 0; i < len; i++) {
        if (col == 0 && (line[i] == ' ' || line[i] == '\t'))
            continue;
        if (col == FOLD){
            while (temp[buffer_index-1] == ' ' || temp[buffer_index-1] == '\t')
                buffer_index--;
                temp[buffer_index++] = '\n';
                col = 0;
                i--;
        } else {
            temp[buffer_index++] = line[i];
            col++;
        }
    }
    temp[buffer_index] = '\0';
    copy(line, temp);
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}