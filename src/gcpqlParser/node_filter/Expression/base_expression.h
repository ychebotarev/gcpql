#pragma once

#include <memory>
#include <iostream>

#include "src/gcpqlParser/common/AstVariant.h"
#include "src/gcpqlParser/node_filter/node_filter_context.h"

namespace gcpql_nodefilter {

	class BaseExpression {
	public:
		BaseExpression() { }
		virtual ~BaseExpression() {  };
		virtual AstVariant Execute(const IFilterContext& context) = 0;
	};

	class BinaryExpression : public BaseExpression {
	public:
		BinaryExpression(BaseExpression* _left, BaseExpression* _right)
			: left(_left), right(_right) {
		}

	protected:
		::std::unique_ptr<BaseExpression> left;
		::std::unique_ptr<BaseExpression> right;
	};

	class UnaryExpression : public BaseExpression {
	public:
		UnaryExpression(BaseExpression* inner_operation_)
			: inner_operation(inner_operation_){
		}

	protected:
		::std::unique_ptr<BaseExpression> inner_operation;

	};
}//end gcpql_nodefilter