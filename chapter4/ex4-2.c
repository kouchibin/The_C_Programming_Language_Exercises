#include <ctype.h>
#include <math.h>

double atof2(char s[])
{
    double val, power, e;
    int i, sign, esign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10.0 + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    if (!isdigit(s[i])){
        esign = (s[i] == '-' ? -1 : 1);
        i++;
    } else
        esign = 1;
    for (e = 0.0; isdigit(s[i]); i++)
        e = e * 10.0 + (s[i] - '0');
    return sign * val / power * pow(10, esign * e);
}