#include <stdio.h>
#include <stddef.h>

char string[] = "aabbccdd";
char string2[20];

size_t strlen(const char str[]) {
    int len = 0;
    while (string[len] != 0)
        len++;
    return len;
}

void mystrcpy(char dst[], const char src[]) {
    int i;
    for (i = 0; src[i] != 0; i++)
        dst[i] = src[i];

    dst[i] = '\0';
}

int main() {
    printf("sizeof(string[0])) = %ld~\n", sizeof(string[0]));
    printf("sizeof(string)) = %ld\n", sizeof(string));
    printf("strlen(string)) = %ld\n", strlen(string));

    mystrcpy(string2, string);
    printf("string2 = %s\n", string2);

    return 0;
}
