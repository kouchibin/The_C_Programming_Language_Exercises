#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Illegal parameters.\n");
        exit(1);
    }
    FILE *p1, *p2;
    p1 = fopen(argv[1], "r");
    p2 = fopen(argv[2], "r");
    char line1[1000], line2[1000];
    int count = 0;
    while (1) {
        count++;
        if (fgets(line1, MAX, p1) == NULL)
            break;
        if (fgets(line2, MAX, p2) == NULL)
            break;
        if (strcmp(line1, line2)) {
            printf("diff:\nIn %s:%d:%s\n", argv[1], count, line1);
            printf("In %s:%d:%s\n", argv[2], count, line2);
            break;
        }
    }
}