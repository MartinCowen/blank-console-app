#include "pch.h"
#include "CppUnitTest.h"
#include "../C_Playground/main.h"
#include "../C_Playground/c_playground.c"
#include "../C_Playground/time_calc.h"
#include "../C_Playground/time_calc.c"

#define ROUND_UDIVIDE(numer, denom) (((numer) + (denom) / 2) / (denom))


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef TESTBUILD

namespace UnitTestU8Division
{
	TEST_CLASS(UnitTestU8Division)
	{
	public:
		
		TEST_METHOD(SpotValues)
		{
			uint8_t n, d, r, act;			

			n = 207;
			d = 5;
			r = 41;

			Assert::AreEqual((uint32_t)r, (uint32_t)divRoundClosest(n, d));
		};

		TEST_METHOD(ZeroDivided)
		{
			uint8_t n, d, r, act;
			float_t expected;

			for (d = 255; d > 0; d--)
			{
				act = divRoundClosest(0, d);
				expected = 0;
				Assert::AreEqual((uint32_t)expected, (uint32_t)act);
			}
		};

		TEST_METHOD(OneDivisor)
		{
			uint8_t n, d, r, act;
			float_t f, expected;

			d = 5;

			for (n = 255; n > 250; n--)
			{
				f = (float_t)n / (float_t)d;
				expected = f + 0.5f;
				//act = divRoundClosest(n, d);
				//act = ROUND_UDIVIDE(n, d);
				act = divRoundClosest(n, d);
				Assert::AreEqual((uint32_t)expected, (uint32_t)act);
			}
		};
		TEST_METHOD(AllNumeratorsAndDivisors)
		{
			uint8_t n, d, r, act;
			float_t f, expected;

			//exhaustively test all u8
			for (d = 255; d > 0; d--)
			{		
				for (n = 255; n > 0; n--)
				{					
					f = (float_t)n / (float_t)d;
					expected = floor((f + 0.5f)); 					
					act = divRoundClosest(n, d);
					Assert::AreEqual((uint32_t)expected, (uint32_t)act);
				}
			}		
		}

			
	};

	TEST_CLASS(CtoFConversion)
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

		TEST_METHOD(BoilingPt)
		{
			uint8_t c, f;
			//boiling point of water
			c = 100;
			f = 212;
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};

		TEST_METHOD(HighBoundC)
		{
			uint8_t c, f;

			//high bound of f
			c = 122;
			f = 248;
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));

		};

		TEST_METHOD(AccuracyRoundDown)
		{
			uint8_t c, f;

			//accuracy - rounding down
			c = 3;
			f = 37;	//37.4
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};

		TEST_METHOD(AccuracyRoundUp7)
		{
			uint8_t c, f;

			//accuracy - rounding up
			c = 7;
			f = 45;	//44.6
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};


		TEST_METHOD(AccuracyRoundUp27)
		{
			uint8_t c, f;

			//accuracy - rounding up
			c = 27;
			f = 81;	//80.6
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};

		TEST_METHOD(AccuracyRoundUp28)
		{
			uint8_t c, f;

			//accuracy - rounding up
			c = 28;
			f = 82;	//82.4
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};

		TEST_METHOD(NoInternalOverflow29)
		{
			uint8_t c, f;

			//29*9=261 which is >255
			c = 29;
			f = 86;	//84.2 but expect 86 due to dividing by 5 first
			Assert::AreEqual((uint32_t)f, (uint32_t)ctof(c));
		};
	};

	TEST_CLASS(TimeCalc)
	{
	public:
		TEST_METHOD(SetTimeZeros)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 0;
			m = 0;
			s = 0;
			
			set_time_hms(h, m, s);
			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};

		TEST_METHOD(SetTimeDistinctHMS)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 1;
			m = 2;
			s = 3;

			set_time_hms(h, m, s);
			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};
		TEST_METHOD(SetTimeInvalidHrs)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 1;
			m = 2;
			s = 3;

			set_time_hms(h, m, s);
			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);

			h = 24;
			
			set_time_hms(h, m, s);

			h = 1;

			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};

		TEST_METHOD(SetTimeInvalidMins)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 1;
			m = 2;
			s = 3;

			set_time_hms(h, m, s);
			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);

			m = 60;

			set_time_hms(h, m, s);

			m = 2;

			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};

		TEST_METHOD(SetTimeInvalidSecs)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 1;
			m = 2;
			s = 3;

			set_time_hms(h, m, s);
			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);

			s = 60;

			set_time_hms(h, m, s);

			s = 3;

			test_time = testing_get_current_time();
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};

		TEST_METHOD(TimeTicksSecsWrap)
		{
			uint8_t h;
			uint8_t m;
			uint8_t s;
			wall_time_t* test_time;

			h = 0;
			m = 0;
			s = 0;

			set_time_hms(h, m, s);
			inc_time();
			test_time = testing_get_current_time();
			
			s = 1;

			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);

			s = 59;

			set_time_hms(h, m, s);
			inc_time();
			test_time = testing_get_current_time();

			s = 0;
			m = 1;
			Assert::AreEqual((uint32_t)h, (uint32_t)test_time->hrs);
			Assert::AreEqual((uint32_t)m, (uint32_t)test_time->mins);
			Assert::AreEqual((uint32_t)s, (uint32_t)test_time->secs);
		};
	};
}

#endif
