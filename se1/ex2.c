/*
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

unsigned int
vgetbits(unsigned int data[],
         unsigned int idx,
         unsigned int len)
{
	unsigned int bits = 0;
	unsigned int aux_bits = 0;
	unsigned int mask = 0;

	unsigned int index;

	/* check for out of range request and exit */
	if ((idx < 0) || (idx + len) / INT_BITS > 1) {
		printf("Out of range\n");
		exit(-1);
	}

	/* 
	 * If we are only on one index of the array, the index and index + len
	 * is equal, we can use the same ideia for get the bits
	 */
	if ((idx / INT_BITS) == ((idx + len) / INT_BITS)) {
		/* transform idx from [0..63] -> [0..31] */
		index = idx % INT_BITS;

		/* shift right data[i] so as to 0'ing the element we want */
		aux_bits = data[idx / INT_BITS] >> index;

		/* create the mask */
		mask = ~(~0 << len);

		/* apply the mask to the needed bits */
		bits = (aux_bits & mask);
	} else {
		/* 
		 * If we have to go to both indexes of the array we need 
		 * to go to one index and then the other
		 * we start from the end to get the high value of bits
		 * and then move to the first index
		 */

		/* set 1 */
		/* transform idx [0..63] to [0..31] */
		index = (idx + len) % INT_BITS;

		/* shift rigth data[i] to 0'ing the index of the element we want */
		aux_bits = data[(idx + len) / INT_BITS];

		/* length of mask */
		len = (idx + len) % INT_BITS;

		/* create the mask */
		mask = ~(~0 << len);

		/* apply the mask to the needed bits */
		bits = (aux_bits & mask);

		/* set 0 */
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

void
vsetbits(unsigned int data[],
         unsigned int idx,
         unsigned int len,
         unsigned int val)
{
	unsigned int mask;
	unsigned int index;

	/* check for out of range request and exit */
	if ((idx < 0) || (idx + len) / INT_BITS > 1) {
		printf("Out of range\n");
		exit(-1);
	}

	/* 
	 * If we are only on one index of the array, the index and index + len
	 * is equal, we can use the same ideia for get the bits
	 */
	if ((idx / INT_BITS) == ((idx + len) / INT_BITS)) {
		/* transform idx [0..63] to [0..31] */
		index = idx % INT_BITS;

		/* set the mask with the for full length and shift to the position */
		mask = (~(~0 << len)) << index;

		/* we shift the value to the position and apply the ~mask 
		 * so we have the value we want surrounded by 1s
		 */
		val = (val << index) | ~mask;

		/* we apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[idx / INT_BITS] = (data[idx / INT_BITS] | mask) & val;
	} else {
		/* 
		 * If we have to go to both indexes of the array we need 
		 * to go to one index and then the other
		 * we start from the end to get the high value of bits
		 * and then move to the first index
		 */

		/* set 1 */
		/* define the index on the array element
		 * transform idx [0..63] to [0..31] */
		index = (idx + len) % INT_BITS;

		/* length of mask */
		len = (idx + len) % INT_BITS;

		/* set the mask with the for full length and shift to the position */
		mask = (~(~0 << len)) << index;

		/* we shift the value to the position and apply the ~mask 
		 * so we have the value we want surrounded by 1s
		 */
		val = (val << index) | ~mask;

		/* we apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[(idx + len) / INT_BITS] = (data[(idx + len) / INT_BITS] | mask) & val;

		/* set 0 */
		/* define the index on the array element
		 * transform idx [0..63] to [0..31] */
		index = (idx - (((idx) / INT_BITS) * INT_BITS));

		/* length of mask */
		len = INT_BITS - index;

		/* set the mask with the for full length and shift to the position */
		mask = (~(~0 << len)) << index;

		/* we shift the value to the position and apply the ~mask 
		 * so we have the value we want surrounded by 1s
		 */
		val = (val << index) | ~mask;

		/* we apply the mask to the data set so as to filter the value
		 * we want to change and finally we change the value
		 */
		data[(idx) / INT_BITS] = (data[(idx) / INT_BITS] | mask) & val;
	}
}

int
main(int argc, char const *argv[])
{
	unsigned int data[2] = {0xABCD1234, 0xFFFFFFEC};
	printf("Get bits: %d\n", vgetbits(data, 0, 8));
	vsetbits(data, 0, 8, 0x0000000F);
	printf("Set bits: %d\n", vgetbits(data, 0, 8));

	printf("Get bits: %d\n", vgetbits(data, 29, 8));
	vsetbits(data, 29, 8, 0x0000000F);
	printf("Set bits: %d\n", vgetbits(data, 29, 8));

	printf("Get bits: %d\n", vgetbits(data, 32, 8));
	vsetbits(data, 32, 8, 0x0000000F);
	printf("Set bits: %d\n", vgetbits(data, 32, 8));
	
	/* terminates */
	printf("Get bits: %d\n", vgetbits(data, 60, 8));
	vsetbits(data, 60, 8, 0x0000000F);

	return 0;
}
