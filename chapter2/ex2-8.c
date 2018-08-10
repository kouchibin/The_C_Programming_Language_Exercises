#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char *byte_to_binary(int x)
{
    static char b[33];
    b[0] = '\0';

    unsigned int z;
    for (z = pow(2, 31); z > 0; z >>= 1)
    {
     
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int rightrot(unsigned int x, int n)
{
    while (n > 0) {
        if (x & 1) {
            x = (x >> 1) | ~(~0U >> 1);
        } else {
            x = x >> 1;
        }
        n--;
    }
    return x;
}

int main()
{   
    printf("%s\n", byte_to_binary(20U));
    printf("%s\n", byte_to_binary(rightrot(20U, 4)));
}