#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "src/gcpqlParser/gcpql_query/gcpql_query_driver.h"
#include "src/gcpqlParser/gcpql_query/gcpql_query_runner.h"

#include "gcpqlQueryContextMock.h"
#include "test_helpers.h"
namespace gcpqlQueryTest
{		
	TEST_CLASS(gcpqlQueryTests)
	{
	public:
		TEST_METHOD(gcpqlQueryestSimple)
		{
            SimpleParse("(actors movies)");
            SimpleParse("select (actors movies)");
            SimpleParse("select (actors played movies)");
            SimpleParse("select (actors as a1 played movies),(movies directors)");

            CheckPath("select (actors movies)", "(actors,movies)");
            CheckPath("select (actors played movies)", "(actors,movies,played)");
            CheckPath("select (actors as a1 played movies),(movies directors)", "(a1,movies,played),(movies,directors)");
        }

        void SimpleParse(const std::string& script)
        {
            gcpql_query::Driver driver;
            auto runner = driver.parse_string(script);
            Assert::IsNotNull(runner, test_helpers::StringToWString(script).c_str());
        }

        void CheckPath(const std::string& script, const std::string& path_in) {
            gcpql_query::Driver driver;
            auto runner = driver.parse_string(script);
            Assert::IsNotNull(runner, test_helpers::StringToWString(script).c_str());

            auto graph_path = runner->GetPath();
            Assert::IsNotNull(graph_path, test_helpers::StringToWString(script).c_str());
            auto path_out = graph_path->ToString();
            Assert::AreEqual(path_in, path_out, test_helpers::StringToWString(script).c_str());

        }
	};
}