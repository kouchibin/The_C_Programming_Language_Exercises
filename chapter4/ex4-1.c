#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[])
{
    int i, j, k;
    int size_s = strlen(s);
    int size_t = strlen(t);
    for (i = size_s-1; i >= 0; i--) {
        for (j = i, k = size_t-1;
             s[j] == t[k] && j > 0 && k > 0;
             j--, k--);
        if (k == 0 && t[k] == s[j]) return j;
    }
    return -1;
}

int main()
{
    char s[] = "abcdefg";
    char t[] = "efb";
    printf("%d\n", strrindex(s, t));
}