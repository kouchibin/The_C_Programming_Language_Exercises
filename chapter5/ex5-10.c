#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100

double stack[MAXSIZE];
int sp = 0;

void push(double v)
{
    if (sp == MAXSIZE)
        printf("error: stack full.\n");
    else 
        stack[sp++] = v;
}

double pop(void)
{
    if (sp == 0) {
        printf("error: empty stack.\n");
        return 0.0;
    } else {
        return stack[--sp];
    }
}

void peek(void)
{
    if (sp > 0)
        printf("%.8g\n", stack[sp-1]);
}

int main(int argc, char *argv[])
{
    
    while (--argc > 0) {
        char *arg = *++argv;
        if (isdigit(arg[0])) {
            double temp;
            temp = atof(arg);
            push(temp);
        }
        else {
            double temp;
            switch (arg[0]) {
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                temp = pop();
                push(pop() - temp);
                break;
            case '/':
                temp = pop();
                push(pop() / temp);
                break;
            default:
                printf("Illegal operator.\n");
                break;
            }
        }
    }
    peek();
}