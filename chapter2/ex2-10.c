#include <stdio.h>

int lower(int c)
{
    return (c >= 'A' && c <='Z') ? c - ('A' - 'a') : c;
}

int main()
{
    int c;
    printf("%d %d\n", 'a', 'A');
    while ((c = getchar()) != EOF){
        printf("%c\n", lower(c));
    }
}