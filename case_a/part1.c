#include<stdio.h>
#include<stdint.h>
#include"bits.h"


int main(int ac, char **av)
{
	uint8_t val1=0b10101010;
	uint8_t val2=0b00001111;
	uint8_t val3=0b11110000;

	print_bits(val1);
	putchar('\n');
	print_bits(val2);
	putchar('\n');
	print_bits(val3);

	return 0;
}
