#pragma once

#include <string>
#include "src/gcpqlParser/common/PODVariant.h"

namespace gcpql_nodefilter {
	class IFilterContext
	{
	public:
		virtual ~IFilterContext() {}
		virtual PODVariant GetProperty(const std::string& property_name) const= 0;
	}; 
}
