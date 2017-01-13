#pragma once

#include "src/gcpqlParser/node_filter/node_filter_context.h"
#include "src/gcpqlParser/common/PODVariant.h"

class FilterContextMock : public gcpql_nodefilter::IFilterContext
{
public:
	virtual PODVariant GetProperty(const std::string& property_name) const
	{
		if (property_name == "int_property_5") return PODVariant(5);
		if (property_name == "int_property_10") return PODVariant(10);
		if (property_name == "int_property_100") return PODVariant(100);
		if (property_name == "long_property_10") return PODVariant(10L);
		if (property_name == "double_property_10") return PODVariant(10.0);
		if (property_name == "bool_property_true") return PODVariant(true);
		if (property_name == "bool_property_false") return PODVariant(false);

		return PODVariant(0);
	};

	static const gcpql_nodefilter::IFilterContext& Instance()
	{
		static FilterContextMock mock;
		return mock;
	}
};

