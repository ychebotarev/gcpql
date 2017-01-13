#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "src/gcpqlParser/node_filter/node_filter_driver.h"
#include "src/gcpqlParser/node_filter/node_filter_runner.h"

#include "FilterContextMock.h"

namespace filterParserTest
{		
	TEST_CLASS(filterParserTests)
	{
	public:
		TEST_METHOD(filterParserTestSimple)
		{
			ExpectTrue("1>0");
			ExpectFalse("1<0");
		}
		
		TEST_METHOD(filterParserTestMixedTypes)
		{
			ExpectTrue("1>0.2");
			ExpectTrue("1<0.9 or true");
				
			ExpectFalse("1<0.9");
			ExpectFalse("1<0.9 and true");
		}

		TEST_METHOD(filterParserTestLogicalExpressions)
		{
			ExpectTrue("true and 2>1");
			ExpectTrue("2>1 and true");
			ExpectTrue("false or 3>2");
			ExpectTrue("3.1 > 2.99 and 4.7 >= 0");
			ExpectTrue("true || 2>1");

			ExpectFalse("false and 2>1");
			ExpectFalse("2>1 and false");
			ExpectFalse("false or 2>3");
			ExpectFalse("3.1 <= 2.99 or 4.7 < 0");
			ExpectFalse("false && 2>1");

			//operation priority check
			ExpectTrue("false and false or true");
			ExpectTrue("true or false and false");

			//test NOT
			ExpectTrue("not false and 2>1");
			ExpectFalse("not true and 2>1");
		}

		TEST_METHOD(filterParserTestComparationExpression)
		{
			ExpectTrue("2>1");
			ExpectTrue("2>=1");
			ExpectTrue("2>=2");
			ExpectTrue("2<3");
			ExpectTrue("2<=3");
			ExpectTrue("3<=3");
			ExpectTrue("3=3");
			ExpectTrue("4!=5");

			ExpectFalse("3<2");
			ExpectFalse("3<3");
			ExpectFalse("3<=2");
			ExpectFalse("3>3");
			ExpectFalse("3>4");
			ExpectFalse("3>=4");
			ExpectFalse("3=4");
			ExpectFalse("4!=4");
		}

		TEST_METHOD(filterParserTestMathExpression)
		{
			ExpectTrue("2+1=3");
			ExpectTrue("2.1+1>3.05");
			ExpectTrue("2.1+1=3.1");
			ExpectTrue("2.1-1>1");
			ExpectTrue("2.1-1=1.100");
			ExpectTrue("2*2=4");
			ExpectTrue("2*2.2=4.4");
			ExpectTrue("2.5*4=10");
			ExpectTrue("10/2=5");
			ExpectTrue("9/2=4.5");
			ExpectTrue("9//2=4");
			ExpectTrue("9/4.5=2");

			//test priority
			ExpectTrue("2+2*2=6");
			ExpectTrue("2*2+2=6");
			ExpectTrue("20-2*2=16");
			ExpectTrue("2+10/2=7");
			ExpectTrue("20-10/2=15");

			//test division by zero
			bool was_exception = false;
			
			try
			{
				gcpql_nodefilter::Driver driver;
				auto runner = driver.parse_string("9/0=2");
				auto result = runner->Execute(FilterContextMock::Instance());
			}
			catch (const std::overflow_error&)
			{
				was_exception = true;
			}

			Assert::IsTrue(was_exception);
			
			was_exception = false;
			try
			{
				gcpql_nodefilter::Driver driver;
				auto runner = driver.parse_string("9/(4.0-4)=2");
				auto result = runner->Execute(FilterContextMock::Instance());
			}
			catch (const std::overflow_error&)
			{
				was_exception = true;
			}
			Assert::IsTrue(was_exception);			
		}

		TEST_METHOD(filterParserTestProperties)
		{
			ExpectTrue("int_property_100 > int_property_10 and (int_property_5 > int_property_10 or int_property_5 >= int_property_5)");
			ExpectTrue("bool_property_true = 1 and 2>=1");

			ExpectFalse("bool_property_false != 0 and 2>1");
		}
		
		TEST_METHOD(filterParserTestBrackets)
		{
			ExpectTrue("(true or false)");
			ExpectFalse("(true and false)");
			ExpectTrue("2*(2+2)=8");
			ExpectTrue("(2+2)*2=8");
			ExpectFalse("false and (false or true)");
			ExpectFalse("(true or false) and false");
		}
		
		TEST_METHOD(filterParserTestParsingErrors)
		{
			ExpectParsingError("1");
			ExpectParsingError("1+");
			ExpectParsingError("1+1");
			ExpectParsingError("1+true");
			ExpectParsingError("true+1");
			ExpectParsingError("2>true+");
			ExpectParsingError("2+>1");
			ExpectParsingError("2++2=4");
			ExpectParsingError("2!2=4");
			ExpectParsingError("true)");
			ExpectParsingError("(true");
			ExpectParsingError("()");
			ExpectParsingError("(true) and");
			ExpectParsingError("and 1");
		}

		TEST_METHOD(filterParserTestCollection)
		{
			ExpectTrue("string_property_a in (\"b\",\"c\",\"a\")");
			ExpectTrue("string_property_a in (string_property_a , \"b\",\"c\")");
			ExpectTrue("int_property_5 in (\"b\", 5, \"c\")");

			ExpectFalse("string_property_a in (\"b\",\"c\")");
			ExpectFalse("string_property_a in (string_property_b,string_property_c)");
			ExpectFalse("int_property_5 in (\"b\",\"c\")");
			ExpectFalse("int_property_5 in (\"b\", 4, int_property_10, \"c\")");
		}

		void ExpectTrue(const std::string& script)
		{
			gcpql_nodefilter::Driver driver;
			auto runner = driver.parse_string(script);
			Assert::IsNotNull(runner, StringToWString(script).c_str());
			auto result = runner->Execute(FilterContextMock::Instance());
			Assert::IsTrue(result.Valid(), StringToWString(script).c_str());
			Assert::IsTrue(result.Is<bool>(), StringToWString(script).c_str());
			Assert::IsTrue(result.IsTrue(), StringToWString(script).c_str());
		}
		
		void ExpectFalse(const std::string& script)
		{
			gcpql_nodefilter::Driver driver;
			auto runner = driver.parse_string(script);
			Assert::IsNotNull(runner, StringToWString(script).c_str());
			auto result = runner->Execute(FilterContextMock::Instance());
			Assert::IsTrue(result.Valid(), StringToWString(script).c_str());
			Assert::IsTrue(result.Is<bool>(), StringToWString(script).c_str());
			Assert::IsFalse(result.IsTrue(), StringToWString(script).c_str());
		}

		void ExpectParsingError(const std::string& script)
		{
			gcpql_nodefilter::Driver driver;
			auto runner = driver.parse_string(script);
			Assert::IsNull(runner, StringToWString(script).c_str());
		}
		
		std::wstring StringToWString(const std::string& s)
		{
			std::wstring temp(s.length(), L' ');
			std::copy(s.begin(), s.end(), temp.begin());
			return temp;
		}	
	};
}