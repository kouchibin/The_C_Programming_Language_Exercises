#include <stdio.h>

int bitcount(unsigned x)
{
    int count = 0;
    while (x != 0){
        count++;
        x &= (x-1);
    }
        
    return count;
}

int main()
{
    unsigned a = 7;
    printf("%d\n", bitcount(a));
}