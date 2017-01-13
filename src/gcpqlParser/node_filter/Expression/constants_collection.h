#pragma once

#include <vector>
#include "base_expression.h"

namespace gcpql_nodefilter {
	
	typedef std::vector<std::unique_ptr<BaseExpression>> BaseExpressionCollection;
	
	class ConstantsCollection {
	public:
		ConstantsCollection() {

		}

		BaseExpressionCollection& Get() {
			return collection;
		}

		void Add(BaseExpression* expression)
		{
			collection.push_back(std::unique_ptr<BaseExpression>(expression));
		}
	private:
		BaseExpressionCollection collection;
	};
}

