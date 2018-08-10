#include <stdio.h>

void strncpy(char *s, char *t, int n)
{
    while (n) {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}

void strncat(char *s, char *t, int n)
{
    while (*s)
        s++;
    while (n) {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}

int strncmp(char *s, char *t, int n)
{
    while (n) {
        if (*s != *t) {
            return (*s - *t);
        }
        s++;
        t++;
        n--;
    }
    return 0;
}

int main()
{
    char s[100];
    char t[100] = "hello, world";
    strncpy(s, t, 5);
    printf("s = %s\n", s);
    strncat(s, t, 4);
    printf("s = %s\n", s);
    printf("%d\n", strncmp(s, t, 5));
}