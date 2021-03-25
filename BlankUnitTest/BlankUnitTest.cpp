#include "pch.h"
#include "CppUnitTest.h"
//TODO: add includes to your main.h and the c files under test. Not the h files of the c files under test.
#include "../BlankConsoleApp/main.h"
#include "../BlankConsoleApp/sample_funcs.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlankUnitTest
{
	TEST_CLASS(BlankUnitTest)
	{
	public:
		
		TEST_METHOD(FreezingPt)
		{
			uint8_t c, f;

			//freezing point of water & low bound of c			
			c = 0;
			f = 32;
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};
	};
}
