#include <stdio.h>
#define MAXLEN 1000

void escape(char s[], char t[])
{
    int i = 0;
    int j = 0;
    while (s[i] != '\0') {
        
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
        }
        i++;
    }
}

void unescape(char from[], char to[])
{
    int i = 0;
    int j = 0;
    while (from[i] != '\0') {
        if (from[i] == '\\'){
            i++;
            switch (from[i]) {
            case 'n':
                to[j++] = '\n';
                break;
            case 't':
                to[j++] = '\t';
                break;
            default:
                to[j++] = from[i];
                break;
            }
        } else {
            to[j++] = from[i];
        }
        i++;
    }
    to[j] = '\0';
}

int main()
{
    char test[MAXLEN] = "hello\tthere\nworld\n";
    printf("%s", test);
    char to[MAXLEN];
    escape(test, to);
    printf("%s\n", to);
    test[0] = '\0';
    unescape(to, test);
    printf("%s", test);
}