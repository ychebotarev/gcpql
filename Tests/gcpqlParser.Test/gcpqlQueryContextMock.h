#pragma once

#include "src/gcpqlParser/gcpql_query/gcpql_query_context.h"
#include "src/gcpqlParser/common/AstVariant.h"

class gcpqlQueryContextMock : public gcpql_query::IQueryContext
{
public:
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

