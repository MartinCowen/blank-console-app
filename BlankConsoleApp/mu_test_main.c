#include <stdint.h>

//Options:
#define STD_OUTPUT_TO_PRINTF			//include this if on host PC platform with printf
//#define STD_OUTPUT_TO_NRF_LOG_INFO		//include this if using SES and Nordic using UART for output messages
#pragma once


#ifdef STD_OUTPUT_TO_PRINTF
#include <stdio.h>	//for printf
#define STD_OUTPUT_LOG printf
#endif
#ifdef STD_OUTPUT_TO_NRF_LOG_INFO
#define STD_OUTPUT_LOG NRF_LOG_INFO
#endif

#include "minunit.h"
//TODO: include your project specific h files here
#include "sample_funcs.h"


//minunit's variables
int mu_tests_run = 0;

#define MAJ 1
#define MIN 00
#define str(s) #s
#define xstr(s) str(s)

#define VERSION_STRING xstr(MAJ) "." xstr(MIN)

//minunit's tests are these functions
//TODO: modify and use this sample test
static char* mu_sampletest1(void)
{
	//declare your input and output variables
	uint8_t c, f;

	//set up the input value and expected value
	c = 100;
	f = 212;

	//assert, message if failed, function call with test for expected value
	mu_assert("mu_sampletest1 Failed", ctof(c) == f);
	return 0;
}


//TODO: more tests go here


//top level test functions
static char* mu_all_tests(void)
{
	STD_OUTPUT_LOG("Version: " VERSION_STRING "\n");

	STD_OUTPUT_LOG("Running MINUNIT mu_sampletest1...\n");
	mu_run_test(mu_sampletest1);
	
	//TODO: call more tests from here
	
	return 0;
}

int mu_test_runner(void)
{
	STD_OUTPUT_LOG("Starting MINUNIT Tests\n");

	char* result = mu_all_tests();
	if (result)
	{
		STD_OUTPUT_LOG("%s\n", result);
	}
	else
	{
		STD_OUTPUT_LOG("ALL MINUNIT TESTS PASSED\n");
	}
	STD_OUTPUT_LOG("MINUNIT Tests run: %d\n", mu_tests_run);
	return result != 0;
}