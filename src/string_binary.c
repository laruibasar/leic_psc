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
 */

#include <stdio.h>

#define NUMBER_RIGHT 4

void
string_binary(char* str, char* tmp)
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
    	for (d = 0; number > 0; d++, number /= 2) {
    		if (d == NUMBER_RIGHT)
    			tmp[d++] = ',';

    		tmp[d] = '0' + number % 2;
    	}
	tmp[d] = 0; /* terminate the string */

	// reverse and affect tmp
	char* p = tmp;
	char* q = tmp + d - 1;
	for (; p < q; p++, q--) {
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
