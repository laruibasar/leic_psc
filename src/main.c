/*-
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Copyright (c) 2019 Luis Bandarra <laruibasar@homestudio.pt>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include <stdio.h>

int main() {
    int char_counter = 0;
    int line_counter = 0;
    int word_counter = 0;

    // state for read char
    // 0 - read spacer
    // 1 - read word
    int state = 0;

    while (1) {
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
