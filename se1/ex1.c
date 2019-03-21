/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2019 Luis Bandarra <luis.bandarra@homestudio.pt>
 * All rights reserved.
 */
#include <stdio.h>

#define DEFAULT_TAB_SIZE 4

int tab_size = DEFAULT_TAB_SIZE;

/*
 * Calculate the string size with the whitespaces
 */
int
string_size_to_whitespace(char *str, int tab_size)
{
	int i = 0;
	char c = str[i];
	int size = 0;

	/* we get the size of the string with the spaces */
	while (c != '\0') {
		if (c == '\t') {
			size += tab_size - (i % tab_size);
		}
		size++;
		c = str[i++];
	}

	return size;
}

/* 
 * Function to solve exercise 1 of SE 1
 * receive a string and tab size and change the \t to whitspace
 */
void
string_detab(char *string, int tab_size)
{
	// discover the real size of the string 
	int size = string_size_to_whitespace(string, tab_size);

	/* we get a new string where we will insert the spaces */
	char new_string[size];

	for (int i = 0, j = 0; i < size; j++) {
		if (string[j] == '\t') {
			for (int m = 0; m < (tab_size - (i % tab_size)); m++) {
				new_string[i++] = ' ';
			}
		} else {
			new_string[i++] = string[j];
		}
	}

	printf("\n%s\n%s\n", new_string, string);
}

int
main()
{

	char str1[] = "ama\tnha\tlogo\tvejo\0";
	string_detab(str1, tab_size);

	char str2[] = "\tvera\tlo\tgo\tvejo\t\tA\0";
	string_detab(str2, tab_size);

	return 0;
}
