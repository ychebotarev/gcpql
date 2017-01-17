#pragma once

#include <string>
#include "src/gcpqlParser/common/AstVariant.h"

namespace gcpql_query {
	class IQueryContext
	{
	public:
		virtual ~IQueryContext() {}
        virtual AstVariant GetPropertyValue(const std::string& property_name) const = 0;
    };
}
