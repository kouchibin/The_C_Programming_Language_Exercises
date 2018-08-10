#include <stdio.h>
#define IN 1
#define OUT 0

// int isdigit(char x)
// {
//     return (x >= '0' && x <= '9');
// }

int ischar(char x)
{
    return (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z');
}

void expand(char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    int status = OUT;
    while (s1[i] == '-')
        i++;
    while (s1[i] != '\0') {

        if ((ischar(s1[i]) || isdigit(s1[i]))) {
            
            if (status == OUT)
                //From this letter
                s2[j++] = s1[i];
            else {
                //To this letter
                for (char c = s2[j-1]+1; c <= s1[i]; c++)
                    s2[j++] = c;
                status = OUT;
            }

        } else if (s1[i] == '-') {
            status = IN;
        }
        i++;
    }
    s2[j] = '\0';
}

int main()
{
    char s0[] = "0-9";
    char s1[] = "a-z";
    char s2[] = "A-Z";
    char s3[] = "a-zA-Z";
    char s4[] = "a-w3-8-";

    char to[100];
    expand(s0, to);
    printf("%s\n", to); 
    expand(s1, to);
    printf("%s\n", to); 
    expand(s2, to);
    printf("%s\n", to); 
    expand(s3, to);
    printf("%s\n", to); 
    expand(s4, to);
    printf("%s\n", to); 


}