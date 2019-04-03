/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2019 Luis Bandarra <luis.bandarra@homestudio.pt>
 * All rights reserved.
 */
#include <stdio.h>

/* union type to store value and interchange  value */
typedef union {
	int inum;
	float fnum;
} Float;

int
string_int(char *string, long *number)
{
	int exp = 0;
	int decimal = 0;
	char c;

	while ((c = string[exp]) != 0) {
		if (c == ',' || c == '.') {
			decimal = 1;
			continue;
		}

		*number = (*number * 10) + (c - '0');
		if (decimal) {
			exp++;
		}
	}

	return exp;
}

float
string_to_float(char *string)
{
	float number = 0;
    // convert string to int

    // shift int to bin for validate

    // convert bin to signal, expoent, mantissa

    // save

	return number;
}

int
main(int argc, char *argv[])
{
    /* code */
	char string[] = "33.635";
	printf("%f", string_to_float(string));

	return 0;
}
