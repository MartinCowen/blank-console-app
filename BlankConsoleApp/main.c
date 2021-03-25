// This project is a blank sample project that shows how to run tests with either MS Test or minuint.
// To run the MS Tests in the BlankUnitTest.cpp file, use the Visual Studio menu Test - Run All Tests (Cntrl+R, A) etc. 
// Results are in the Test Explorer window (Cntrl+E, T)
// To debug MS tests, need to use the Test menu option eg Cntrl+R, Cntrl+A not the Debug menu (F5/F11)
// To run the minunit tests, build and run (F5). 
// Results are shown on the console window (this is a Windows console application). See mu_test_main for options to redirect the results to NRF_LOG_INFO for SES, or add another option.
// To debug minunit tests, set breakpoints in code under test or in tests, use F11 to step etc.


#define TESTING_WITH_MINUNIT	//include this if you want to run tests with minunit, otherwise that code is not included
#include <stdint.h>
//TODO: add your project specific h files here


#ifdef TESTING_WITH_MINUNIT
int mu_test_runner(void);
#endif

int main(void)
{

#ifdef TESTING_WITH_MINUNIT	//run the tests
	int mu_result = mu_test_runner();

	if (mu_result)
		return mu_result;
#endif	
}

