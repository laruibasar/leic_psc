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

#define SIZE 64

char line_current[SIZE], line_long[SIZE];
int line_current_dim, line_long_dim;

// int mygetline(char line[], int dim) {
//    int i;
//    char ch;

//    for (i = 0; i < dim - 1; i++) {
//        ch = getchar();

//      if (ch == '\n' && ch == EOF)
//            break;

//        line[i] = c;
//    }

//    line[i] = '\0';
//    return i;
// }


// 2 version
int mygetline(char line[], int dim) {
    int i;
    char ch;

    for (i = 0; i < dim -1 ; i++) {
        ch = getchar();
        if (ch == EOF && i == 0)
            return -1;

        if (ch == '\n')
            break;

        line[i] = ch;
    }
    line[i] = '\0';
    return i;
}

void linecpy(char dst[], char src[], int dim) {
    for (int i = 0; i < dim; i++) {
        dst[i] = src[i];
    }
}

int main() {
    while ((line_current_dim =
            mygetline(line_current, sizeof(line_current))) >= 0) {
        if (line_current_dim > line_long_dim) {
            line_long_dim = line_current_dim;

            linecpy(line_long, line_current, line_current_dim);
        }

        line_long[line_long_dim] = '\0';
        printf("%s\n", line_long);
    }
}
