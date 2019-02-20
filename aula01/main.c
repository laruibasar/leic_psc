#include <stdio.h>

int main() {
    int char_counter = 0;
    int line_counter = 0;
    int word_counter = 0;

    // state for read char
    // 0 - read spacer
    // 1 - read word
    int state = 0;

    while(1) {
       int c = getchar();
       if (c == -1)
           break;
       if (c == '\n')
           line_counter++;

       if (c == ' ' || c == '\t' || c == '\n') {
           if (state == 1) 
               state = 0; 
       } else {
           if (state == 0) { 
               state = 1;
               word_counter++;
           }
       }

       putchar(c);
       char_counter++;
    }

   printf("Numero total de caracteres= %d\n", char_counter);
   printf("Numero total de linhas = %d\n", line_counter);
   printf("Numero total de palavras = %d\n", word_counter);

}
