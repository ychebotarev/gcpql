#pragma once

#include "Expression\base_expression.h"
#include "node_filter_context.h"

namespace gcpql_nodefilter {
	class Runner
	{
	public:
		void SetRootExpression(BaseExpression* _root) {
			root = std::unique_ptr<BaseExpression>(_root);
		}

		AstVariant Execute(const IFilterContext& context) {
			return root->Execute(context);
		}

	private:
		std::unique_ptr<BaseExpression> root;

	};
}//end of nodefilter namespace

