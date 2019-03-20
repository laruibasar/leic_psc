/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2019 Luis Bandarra <luis.bandarra@homestudio.pt>
 * All rights reserved.
 */
#include <stdio.h>

typedef struct citizen_node {
    const char *name, *civil_id_no;
    unsigned polling_place;
    struct citizen_node *next;
} Citizen_node;

int
main(int argc, char *argv[])
{
    /* code */
    return 0;
}
