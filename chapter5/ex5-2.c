#include <stdio.h>
#include <ctype.h> 
#define SIZE 5

int main()
{
    int n, ret, getfloat(double *);
    double array[SIZE];
    for (n = 0; n < SIZE && (ret = getfloat(&array[n])) != EOF; n++)
        if (ret != 0)
            printf("current read:%g\n", array[n]);
}

int getfloat(double *p)
{
    int getch(void);
    void ungetch(int);

    int c, sign, sawsign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (sawsign = (c == '+' || c == '-'))
        c = getch();
    if (!isdigit(c)) {
        ungetch(c);
        if (sawsign)
            ungetch(sign == 1 ? '+' : '-');
        return 0;
    }
    for (*p = 0.0; isdigit(c); c = getch())
        *p = 10.0 * *p + (c - '0');
    if (c == '.')
        c = getch();
    double power = 10.0;
    while (isdigit(c)) {
        *p += ((c - '0') / power);
        power *= 10;
        c = getch();
    }
    *p *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}