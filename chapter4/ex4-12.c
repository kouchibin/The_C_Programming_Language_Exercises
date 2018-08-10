#include <stdio.h>

void itoa(int v, char s[])
{
    int digit = v % 10;
    if (v / 10)
        itoa(v / 10, s);
    int i = 0;
    while (s[i] != '\0')
        i++;
    s[i++] = '0' + digit;
    s[i] = '\0'; 
}

int main()
{
    char s[100];
    s[0] = '\0';
    itoa(12345, s);
    printf("%s\n", s);
}