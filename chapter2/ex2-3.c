#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int htoi(char h[]);

int main() {
    int c;
    int i = 0;
    char h[MAX];
    while ((c = getchar()) != EOF) {
        if (c != '\n')
            h[i++] = c;
        else {
            h[i] = '\0';
            printf("%d\n", htoi(h));
            i = 0;
        }
            
    }
}

int htoi(char h[]) {
    int i = 0;
    if (h[0] == '0' && (h[1] == 'x' || h[1] == 'X'))
        i = 2;
    int value = 0;
    int digit = 0;
    while (h[i] != '\0'){
        if (h[i] >= '0' && h[i] <= '9')
            digit = h[i] - '0';
        else if (h[i] >= 'a' && h[i] <= 'f')
            digit = h[i] - 'a' + 10;
        else if (h[i] >= 'A' && h[i] <= 'F')
            digit = h[i] - 'A' + 10;
        else 
            exit(0);
        value = value * 16 + digit;
        i++;
    }
    return value;
}