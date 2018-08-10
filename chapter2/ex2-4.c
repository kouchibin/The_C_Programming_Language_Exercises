#include <stdio.h>

void squeeze(char s1[], char s2[]);
int in(int c, char s[]);

int main()
{
    char text[] = "hello, world\n";
    char s[] = "hld";
    squeeze(text, s);
    printf("%s", text);
}

void squeeze(char s1[], char s2[])
{
    int i = 0, j = 0;
    while (s1[i] != '\0'){
        while (in(s1[i], s2))
            i++;
        s1[j++] = s1[i++]; 
    }
    s1[j] = '\0';
}

int in(int c, char s[])
{
    int i = 0;
    while (s[i] != '\0')
        if (s[i++] == c)
            return 1;
    return 0;
}