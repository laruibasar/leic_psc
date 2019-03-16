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
string_size_to_whitespace(char *str, int tab_size) {
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

/* Function for exercise 1 of SE 1
 * receive a string and tab size and change the \t to whitspace
 */
void
string_detab(char *string, int tab_size)
{
    int size = string_size_to_whitespace(string, tab_size);

    /* we get a new string where we will insert the spaces */
    char new_string[size];

    for (int i = 0, j = 0; i < size; j++) {
        if (string[j] == '\t') {
            int t = tab_size - (i % tab_size);
            for (int m = 0; m < t; m++) {
                new_string[i++] = ' ';
            }
        } else {
            new_string[i++] = string[j];
        }
    }

    printf("\n%s\n%s\n", new_string, string);
}

/*
 * Set option from command line
 */
void
set_options(int c, char *av[])
{
    int i = 0;
    while (i < c) {
        printf("c: %d\ti:%d\t%s\n", c, i, av[i]);
        i++;
    }
}

int
main(int argc, char *argv[])
{
    if (argc > 1)
        set_options(argc, argv);

    char str[] = "ama\tnha\tlogo\tvejo\0";

    string_detab(str, tab_size);

    return 0;
}
