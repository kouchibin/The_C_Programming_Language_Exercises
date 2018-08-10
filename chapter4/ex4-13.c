#include <stdio.h>
#include <string.h>

void reverse_helper(char s[], int i, int j)
{
    if (i >= j)
        return;
    else {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverse_helper(s, i+1, j-1);
    }
}

void reverse(char s[])
{
    reverse_helper(s, 0, strlen(s) - 1);
}

int main()
{
    char s[] = "abcdefg";
    reverse(s);
    printf("%s\n", s);
}