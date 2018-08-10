#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *a;
    void *malloc(size_t);
    a = malloc(20 * sizeof(int));
    for (int i = 0; i < 20; i++)
        printf("%d ", a[i]);
}