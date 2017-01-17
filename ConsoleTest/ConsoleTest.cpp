// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <chrono>
#include "src/gcpqlParser/common/AstVariant.h"

#include "src/gcpqlParser/gcpql_query/gcpql_query_driver.h"
#include "src/gcpqlParser/gcpql_query/gcpql_query_runner.h"
#include "src/gcpqlParser/gcpql_query/gcpql_query_context.h"

using namespace gcpql_query;

class gcpqlQueryContextMock : public IQueryContext
{
public:
    gcpqlQueryContextMock() {
		string_a = "a";
		string_b = "b";
		string_c = "c";
	}
	virtual AstVariant GetPropertyValue(const std::string& property_name) const
	{
		if (property_name == "int_property_5") return AstVariant(5);
		if (property_name == "int_property_10") return AstVariant(10);
		if (property_name == "int_property_100") return AstVariant(100);
		if (property_name == "long_property_10") return AstVariant(10L);
		if (property_name == "double_property_10") return AstVariant(10.0);
		if (property_name == "bool_property_true") return AstVariant(true);
		if (property_name == "bool_property_false") return AstVariant(false);
		if (property_name == "string_property_a") return AstVariant((char*)string_a.c_str());
		if (property_name == "string_property_b") return AstVariant((char*)string_b.c_str());
		if (property_name == "string_property_c") return AstVariant((char*)string_c.c_str());

		return AstVariant(0);
	};

	static const IQueryContext& Instance()
	{
		static gcpqlQueryContextMock mock;
		return mock;
	}
private:
	std::string string_a;
	std::string string_b;
	std::string string_c;
};

void RunQuery(const std::string& script)
{
	gcpql_query::Driver driver;
	auto runner = driver.parse_string(script);
    gcpqlQueryContextMock context;
	auto result = runner->Execute(context);
	delete runner;
}

void CompileQuery(const std::string& script)
{
    gcpql_query::Driver driver;
	auto runner = driver.parse_string(script);
	delete runner;
}

int main()
{
	{
		//CompileQuery("true and true or fal");
		//RunQuery("int_property_100 > 1d");
		auto start = std::chrono::high_resolution_clock::now();

		size_t interation = 1000000;

		for (auto size = 0; size < interation; ++size) {
			RunQuery("int_property_100 > int_property_10 and (int_property_5 > int_property_10 or int_property_5 >= int_property_5)");
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "Time to run " << interation << " interations is compile and execute is  : " << (diff.count() * 1000.0 / 100000.0) << " ms\n";
	}
	//_CrtDumpMemoryLeaks();

    return 0;
}



