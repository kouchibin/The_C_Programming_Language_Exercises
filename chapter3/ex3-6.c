#include <stdio.h>
#include <string.h>
#include <math.h>

void reverse(char s[])
{
    int i = 0;
    int j = strlen(s) - 1;
    int c;
    for (; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[], int width)
{
    int sign, i;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    while (i < width)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[100];
    for (int i = -100; i < 100; i++){
        itoa(i, s, 4);
        printf("%s\n",s);
    }
}