#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#define BUFSIZE 100

int getop(char s[])
{
    static int buf = EOF;

    int i, c;
    i = 0;

    if (buf != EOF){
        c = buf;
        buf = EOF;
    } else 
        c = getchar();
        
    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';
    
    // Is an operator but '-' may represent negative number
    // so we need to deal with that seperately.
    if (!isalpha(c) && !isdigit(c) && c != '.' && c != '-')
        return c;

    // Is an character, which means it is a command if strlen() > 1
    // or a variable if strlen() == 1.
    if (isalpha(c)){
        while (isalpha(s[++i] = c = getchar()))
            ;
        s[i] = '\0';
        if (strlen(s) > 1)
            return COMMAND;
        else 
            return VAR; 
    }

    // Check if '-' is followed by number to decide if it
    // represent negative number.
    if (((c = getchar()) == ' ' || c == '\t' || c == '\n') && s[0] == '-')
        return c;
    buf = c;

    
    if (isdigit(s[i]) || s[i] == '-') {
        if (buf != EOF){
            s[++i] = c = buf;
            buf = EOF;
        } 
        while (isdigit(c)) 
            s[++i] = c = getchar();
    }

        
    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        buf = c;
    return NUMBER;
}
