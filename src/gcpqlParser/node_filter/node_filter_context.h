#pragma once

#include <string>
#include "src/gcpqlParser/common/AstVariant.h"

namespace gcpql_nodefilter {
	class IFilterContext
	{
	public:
		virtual ~IFilterContext() {}
		virtual AstVariant GetPropertyValue(const std::string& property_name) const= 0;
	}; 
}
