#include <stdio.h>
#define MAXLEN 1000
#define TAB_SIZE 7

int get_line(char line[], int limit);
void entab(char line[], int len);

int main()
{   
    char line[MAXLEN];
    int len;
    while ((len = get_line(line, MAXLEN)) != 0) {
        entab(line, len);
        printf("%s", line);
    }
}

int get_line(char line[], int limit)
{
    int c, i;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

void entab(char line[], int len)
{
    int i, j, space_count;
    for (i = j = space_count = 0; i < len; i++) {
        if (line[i] == ' ') {
            space_count++;
            if (space_count == TAB_SIZE){
                line[j++] = '\t';
                space_count = 0;
            }
        } else {
            while (space_count > 0){
                line[j++] = ' ';
                space_count--;
            }
            line[j++] = line[i];
        }
    }
    line[j] = '\0';
}