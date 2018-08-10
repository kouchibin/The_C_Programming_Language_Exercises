#include <stdio.h>

void strcat(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++)
        ;
}

int main()
{
    char s[] = "hello, ";
    char t[] = "world.";
    strcat(s, t);
    printf("%s\n", s);
}