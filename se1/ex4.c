/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2019 Luis Bandarra <luis.bandarra@homestudio.pt>
 * All rights reserved.
 */

#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof a / sizeof a[0])

typedef struct citizen_node {
	const char *name, *civil_id_no;
	unsigned polling_place;
	struct citizen_node *next;
} Citizen_node;

void
group_by_polling_place(Citizen_node places[],
                       Citizen_node all[],
                       size_t all_num)
{
	Citizen_node *p = all;
	for(size_t i = 1; i < all_num + 1; i++) {
		unsigned int place = p->polling_place;
        Citizen_node e = places[place];

		if (e == NULL) {
			printf("has citizen_node\n");
        } else {
            printf("Size different\n");
        }

		*p = all[i];
	}
}

int
main(int argc, char *argv[])
{
	Citizen_node places[10];

	Citizen_node all[10];
	all[0].name = "Ana";
	all[0].civil_id_no = "1";
	all[0].polling_place = 0;

	all[1].name = "Bruno";
	all[1].civil_id_no = "3";
	all[1].polling_place = 1;

	all[2].name = "Carla";
	all[2].civil_id_no = "4";
	all[2].polling_place = 0;

	all[3].name = "Daniel";
	all[3].civil_id_no = "7";
	all[3].polling_place = 3;

	all[4].name = "Eva";
	all[4].civil_id_no = "12";
	all[4].polling_place = 2;

	all[5].name = "Filipe";
	all[5].civil_id_no = "42";
	all[5].polling_place = 1;

	all[6].name = "Gabriela";
	all[6].civil_id_no = "35";
	all[6].polling_place = 0;

	all[7].name = "Hugo";
	all[7].civil_id_no = "53";
	all[7].polling_place = 0;

	all[8].name = "Iva";
	all[8].civil_id_no = "23";
	all[8].polling_place = 1;

	all[9].name = "Joao";
	all[9].civil_id_no = "18";
	all[9].polling_place = 3;

	group_by_polling_place(places, all, ARRAY_SIZE(all));

	return 0;
}
