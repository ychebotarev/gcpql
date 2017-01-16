#pragma once

#include "src/gcpqlParser/gcpql_query/gcpql_query_context.h"
#include "src/gcpqlParser/common/AstVariant.h"

class gcpqlQueryContextMock : public gcpql_query::IQueryContext
{
public:
	static const gcpql_query::IQueryContext& Instance()
	{
		static gcpqlQueryContextMock mock;
		mock.string_a = "a";
		mock.string_b = "b";
		mock.string_c = "c";
		return mock;
	}
private:
	std::string string_a;
	std::string string_b;
	std::string string_c;
};

