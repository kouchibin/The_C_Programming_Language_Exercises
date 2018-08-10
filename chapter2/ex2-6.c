#include <stdio.h>

int setbits(int x, int p, int n, int y)
{
    int mask = ~(~0 << n);
    y = (mask & y) << (p - n + 1);
    int mask2 = ~(mask << (p - n + 1));
    x = x & mask2;
    x = x | y;
    return x;
}

int main()
{
    printf("%d\n", setbits(15, 8, 4, 20));
}