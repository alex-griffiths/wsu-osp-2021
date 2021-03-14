#include<stdio.h>
#include<stdint.h>
#include"bits.h"

void print_bits(uint8_t value)
{
	int i;

	/*
	 * Iterate from 0 to 7 creating a masking that extracts the bit at the 
	 * ith position.
	 */
	for (i = 7; i >= 0; i--)
	{
		printf("%d", (value & (1 << i)) >> i);
	}
}

uint8_t reverse_bits(uint8_t value)
{
	uint8_t final_val = 0;
	uint8_t cur_val = 0;
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		/* 
		 * Get the value of the current bit and push it on to the end of 
		 * the final value
		 */
		cur_val = (value & (1 << i)) >> i;
		final_val = (final_val << 1) | cur_val;
	}

	return final_val;
}

uint8_t check_bit(uint8_t value, uint8_t bit)
{
	uint8_t mask = 1 << bit;

	return value & mask;
}

uint8_t toggle_bit(uint8_t *value, uint8_t bit)
{
	*value ^= 1 << bit;

	return value;
}

uint8_t get_subfield(uint8_t value, uint8_t start, uint8_t stop)
{
	/* 
	 * Shift value left so the upper bits exceed the value size.
	 * This makes the MSB one end of our subfield.
	 */
	value = value << (7 - stop);

	/*
	 * Shift the value right so that now the LSB is the end of
	 * our subfield
	 */
	value = value >> (7 - (stop - start));

	return;
}
