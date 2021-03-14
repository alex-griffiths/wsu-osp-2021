#include<stdio.h>
#include<stdint.h>
#include"bits.h"


int main(int ac, char **av)
{
	uint8_t val=0b10101010;
	uint8_t bit;

	print_bits(val);
	putchar('\n');

	for(bit=0;bit<8;bit++)
	{
		printf("Bit %u is",bit);
		if(check_bit(val,bit))
		{
			printf(" on\n");
		}
		else
		{
			printf(" off\n");
		}
	}

	return 0;
}
