#include <stdio.h>
#include <string.h>

int strend(char *s, char *t)
{
    s += strlen(s);
    char *t_start = t;
    t += strlen(t);
    while (*--s == *--t)
        if (t_start == t)
            return 1;
        ;
    return 0;

}

int main()
{
    char s[] = "hello, world";
    char t[] = "ord";
    printf("%d\n",strend(s, t));
}