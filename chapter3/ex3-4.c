#include <stdio.h>
#include <math.h>
#include <limits.h>

void reverse(char s[])
{
    int c, i;
    int len = strlen(s);
    for (i = 0; i < len / 2; i++) {
        c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
}

void itoa(int n, char s[])
{
    int sign, i;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10));
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[1000];
    printf("%d\n", INT_MIN);
    itoa((long)INT_MIN, s);
    printf("%s\n", s);

    unsigned us;
    int i = -100;
    us = i;
    printf("%u\n", us);
    printf("%d\n", us);
}