#include <stdio.h>

int in(int c, char s[])
{
    int i = 0;
    while (s[i] != '\0')
        if (s[i++] == c)
            return 1;
    return 0;
}

int any(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0'){
        if (in(s1[i], s2))
            return i;
        i++;
    }
    return -1;
}

int main()
{
    char s1[] = "hello, world!\n";
    char s2[] = "lw";
    char s3[] = "bs";
    printf("%d\n", any(s1, s2));
    printf("%d\n", any(s1, s3));
}

