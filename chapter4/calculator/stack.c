#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("stack empty\n");
        return 0.0;
    }
}

void peek(void)
{
    if (sp > 0)
        printf("\t%.8g\n", val[sp - 1]); 
    else 
        printf("stack empty\n");
}

void clear(void)
{
    sp = 0;
}