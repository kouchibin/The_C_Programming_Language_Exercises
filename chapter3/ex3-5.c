#include <stdio.h>

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

void itob(int n, char s[], int b)
{
    int i = 0;
    int digit;
    do {
        digit = n % b;
        if (digit > 9) {
            s[i++] = 'A' + digit - 10;
        } else {
            s[i++] = '0' + digit;
        }
    } while (n /= b);
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[20];
    itob(100, s, 10);
    printf("%s\n", s);
    itob(15, s, 16);
    printf("%s\n", s);
    itob(7, s, 2);
    printf("%s\n", s);

}