#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int c;
    printf("%s\n", argv[0]);
    if (strcmp(argv[0], "./upper") == 0) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    } else if (strcmp(argv[0], "./lower") == 0) {
        while ((c = getchar()) != 0) 
            putchar(tolower(c));
    }
}