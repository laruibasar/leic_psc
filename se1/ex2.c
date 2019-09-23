/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2019 Luis Bandarra <luis.bandarra@homestudio.pt>
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
/*
 * INT_BIT sets the dimension of the data stored in a data set
 * occuping 1 ints (32 bits)
 */
#define INT_BITS 32

/* Check for the indexes values and terminate if out of bounds */
void
check_dimension(unsigned int start_value, unsigned int end_value)
{
	if ((start_value < 0) || (end_value) / INT_BITS > 1) {
		printf("Out of range\n");
		exit(-1);
	}
}

/*
 * This function get the choosen bits from the index and length
 * from the dataset passed to the function.
 * We can have two situations:
 * 1. The bits are in the same dataset
 * 2. The bits cross several datasets
 * 	In this case we need to get the values first from dataset 1
 *  and then for the dataset 0.
 */
unsigned int
vgetbits(unsigned int data[],
         unsigned int idx,
         unsigned int len)
{
	unsigned int bits = 0;
	unsigned int aux_bits = 0;
	unsigned int mask = 0;

	unsigned int index;
	unsigned int idx_end = idx + len;

	/* check for out of range request */
	check_dimension(idx, idx + len);

	/*
	 * If we are only on one index of the array, the index and index + len
	 * is equal, we can use the same ideia for get the bits
	 */
	if ((idx / INT_BITS) == ((idx_end) / INT_BITS)) {
		/* transform idx from [0..63] -> [0..31] */
		index = idx % INT_BITS;

		/* shift right data[i] so as to 0'ing the element we want */
		aux_bits = data[idx / INT_BITS] >> index;

		/* create the mask */
		mask = ~(~0 << len);

		/* apply the mask to the needed bits */
		bits = (aux_bits & mask);
	} else {
		/* dataset 1 */
		/* we know we are at begining of the second dataset */
		index = 0;
		aux_bits = data[(idx_end) / INT_BITS];

		/* length of mask */
		len = (idx_end) % INT_BITS;

		/* create the mask */
		mask = ~(~0 << len);

		/* apply the mask to the needed bits */
		bits = (aux_bits & mask);

		/* dataset 0 */
		/* transform idx [0..63] to [0..31] */
		index = idx % INT_BITS;

		/* shift rigth data[i] to 0'ing the index of the element we want */
		aux_bits = (data[idx / INT_BITS] >> index);

		/* length of mask */
		len = INT_BITS - index;

		/* create the mask */
		mask = ~(~0 << len);

		/* shift to apply the get space for the new value */
		bits = bits << len;

		/* apply the mask to the needed bits */
		bits = bits | (aux_bits & mask);
	}

	return bits;
}

/*
 * This function set the choosen bits to the value (val)
 * we send in the arguments.
 * We can have two situations:
 * 1. the interval to change is in the same dataset (general rule)
 *
 * 2. the interval cross two datasets (special case)
 *    In this case we need to make two passes with diferent lenghts
 */
void
vsetbits(unsigned int data[],
         unsigned int idx,
         unsigned int len,
         unsigned int val)
{
	unsigned int mask = 0;
	unsigned int index = 0;

	unsigned int aux_val;
	unsigned int aux_len = len;
	unsigned int idx_end = idx + len;


	/* check for out of range request */
	check_dimension(idx, idx_end);

	/*
	 * General rule
	 */
	if ((idx / INT_BITS) == ((idx_end) / INT_BITS)) {
		printf("%x\t%x\n", data[1], data[0]);
		/* transform idx [0..63] to [0..31] */
		index = idx % INT_BITS;

		/* set the mask with the for full length
		 * and shift to the position */
		mask = (~(~0 << aux_len)) << index;

		/* we shift the value to the position and apply the ~mask
		 * so we have the value we want surrounded by 1s
		 */
		aux_val = (val << index) | ~mask;

		/* we apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[idx / INT_BITS] = (data[idx / INT_BITS] | mask) & aux_val;
		printf("%x\t%x\n", data[1], data[0]);
	} else {
		/*
		 * Special case:
		 * we have to go to both indexes of the array
		 * so we ajust the lenght to the value to match the dataset
		 */
		printf("%x\t%x\n", data[1], data[0]);

		/* dataset 0 */
		index = idx % INT_BITS; /* not needed her, index = idx*/

		/* we define the lenght of the mask, split the datasets */
		aux_len = len - ((idx_end) % INT_BITS);

		/* we set the mask */
		mask = (~(~0 << aux_len)) << index;

		/* we shift the value to the position and apply the ~mask
		 * so we have the value we want surrounded by 1s
		 */
		aux_val = (val << index) | ~mask;

		/* we also apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[idx / INT_BITS] = (data[idx / INT_BITS] | mask) & aux_val;

		/* dataset 1 */
		/* 0 because we are at the start next dataset */
		index = 0;

		/* we set the mask for the rest of value */
		mask = (~(~0 << (len - aux_len))) << index;

		/* we shift the value to remove the used value
		 * and apply the ~mask
		 */
		aux_val = (val >> aux_len) | ~mask;

		/* we also apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[idx_end / INT_BITS] = (data[idx_end / INT_BITS] | mask) & aux_val;
		printf("%x\t%x\n", data[1], data[0]);
	}
}

int
main(int argc, char const *argv[])
{
	unsigned int data_1[2] = {0xABCD1234, 0xFFFFFFEC};
	printf("1:\tGet bits: %x\n", vgetbits(data_1, 0, 8));

	vsetbits(data_1, 0, 8, 0x0000000F);
	printf("> Set bits (0x0000000F): %x\n", vgetbits(data_1, 0, 8));

	unsigned int data_2[2] = {0xABCD1234, 0xFFFFFFEC};


	printf("2:\tGet bits: %x\n", vgetbits(data_2, 29, 8));
	vsetbits(data_2, 29, 8, 0x0000000F);
	printf("> Set bits (0x0000000F): %x\n", vgetbits(data_2, 29, 8));

	unsigned int data_3[2] = {0xABCD1234, 0xFFFFFFEC};
	printf("3:\tGet bits: %x\n", vgetbits(data_3, 32, 8));
	vsetbits(data_3, 32, 8, 0x0000000F);
	printf("> Set bits (0x0000000F): %x\n", vgetbits(data_3, 32, 8));

	/* terminates */
	printf("4:\tGet bits: %x\n", vgetbits(data_1, 60, 8));
	vsetbits(data_1, 60, 8, 0x0000000F);

	return 0;
}
