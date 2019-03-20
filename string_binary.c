#include <stdio.h>

#define NUMBER_RIGHT 4

void 
string_binary(char *str, char *tmp)
{
    int number = 0;
    int x = 0;
    int flag = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ',' || str[i] == '.') {
            flag = 1;
            continue;
        }
        number = number * 10 + str[i] - '0';
        
        if (flag)
            x++;
    }

    // use of  N x 2^y / 10^x = b______,____ (,y)
    number = number << NUMBER_RIGHT;

    // for divide by 10^x we use for cycle
    for (int i = 0; i < x; i++)
        number /= 10;

    // convert bin -> string bin
    int d;
    //char binary[100];
    for (d = 0; number > 0; d++, number /= 2) { 
        if (d == NUMBER_RIGHT)
            tmp[d++] = ',';

        tmp[d] = '0' + number % 2;
    }
    tmp[d] = 0;  /* terminate the string */
    
    // reverse and affect tmp
    char *p = tmp;
    char *q = tmp + d - 1;
    for ( ; p < q; p++, q--) {
        char a = *p;
        *p = *q;
        *q = a;
    }
}

int
main()
{
    char tmp[100];
    char dec_number[] = "33,625";
    string_binary(dec_number, tmp);

    printf("%s in decimal => %s in binary\n", dec_number, tmp);

    return 0;
}
