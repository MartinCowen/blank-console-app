#include "sample_funcs.h"

//sample function under test
//converts celsius to Fahrenheit
uint8_t ctof(uint8_t c)
{	//simple version, rounds fractions down
	uint8_t i;

	if (c < 255 / 9)
	{
		i = c * 9;
		i /= 5;
	}
	else
	{
		i = c / 5;
		i *= 9;
	}

	i += 32;

	return i;
}