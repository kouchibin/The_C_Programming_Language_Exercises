#include <stdio.h>

int invert(int x, int p, int n)
{
    int mask = ~(~0 << n) << (p - n + 1);
    return mask ^ x;
}

int main()
{
    printf("%d\n", invert(20, 5, 4));
}