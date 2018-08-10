#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"
#define MAXOP 100

double variables[26];

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    extern int sp;
    extern double val[];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0)
                printf("error: zero divisior\n");
            else 
                push(pop() / op2);
            break;
        case '%':
            op2 = pop();
            push((int) pop() % (int) op2);
            break;
        case COMMAND:
            if (!strcmp("peek", s))
                peek();
            if (!strcmp("dup", s)) {
                double temp = pop();
                push(temp);
                push(temp);
            }
            if (!strcmp("swap", s)) {
                double temp1 = pop();
                double temp2 = pop();
                push(temp1);
                push(temp2);
            }
            if (!strcmp("clear", s))
                clear();
            if (!strcmp("sin", s)){
                push(sin(pop()));
                peek();
            }
            if (!strcmp("exp", s)){
                push(exp(pop()));
                peek();
            }
            if (!strcmp("pow", s)){
                int power = pop();
                int val = pop();
                push(pow(val, power));
                peek();
            }
            if (!strcmp("let", s)) {
                char v_name;
                int t;
                while (!isalpha(v_name = getchar()))
                    ;
                if ((t = getop(s)) == NUMBER) {
                    variables[v_name - 'a'] = atof(s);
                }
                // Ignore the trailing '\n' 
                getchar();
            }
            if (!strcmp("get", s)) {
                char v_name;
                int t;
                while (!isalpha(v_name = getchar()))
                    ;
                printf("%c = %g\n", v_name, variables[v_name - 'a']);
                getchar();
            }
            break;
        case VAR:
            push(variables[s[0] - 'a']);
            break;
        case '\n':
            peek();
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}