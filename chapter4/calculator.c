#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define COMMAND 'C'
#define VAR 'V'

int getop(char []);
void push(double);
double pop(void);
void peek(void);
void clear(void);
int getch(void);

double variables[26];
double lastprint;

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
                while (!isalpha(v_name = getch()))
                    ;
                if ((t = getop(s)) == NUMBER) {
                    variables[v_name - 'a'] = atof(s);
                }
                // Ignore the trailing '\n' 
                getch();
            }
            if (!strcmp("get", s)) {
                char v_name;
                int t;
                while (!isalpha(v_name = getch()))
                    ;
                printf("%c = %g", v_name, variables[v_name - 'a']);
                getch();
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

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;
    i = 0;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    
    // Is an operator but '-' may represent negative number
    // so we need to deal with that seperately.
    if (!isalpha(c) && !isdigit(c) && c != '.' && c != '-')
        return c;

    // Is an character, which means it is a command if strlen() > 1
    // or a variable if strlen() == 1.
    if (isalpha(c)){
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (strlen(s) > 1)
            return COMMAND;
        else 
            return VAR; 
    }

    // Check if '-' is followed by number to decide if it
    // represent negative number.
    if (((c = getch()) == ' ' || c == '\t' || c == '\n') && s[0] == '-')
        return c;
    ungetch(c);

    
    if (isdigit(s[i]) || s[i] == '-')
        while (isdigit(s[++i] = c = getch())) 
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}