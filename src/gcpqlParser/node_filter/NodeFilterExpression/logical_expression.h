#pragma once
#include <memory>
#include "base_expression.h"

namespace gcpql_nodefilter {
	class LogicalExpressionAnd : public BinaryExpression {
	public:
		LogicalExpressionAnd(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right)  {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			if (!left_result.IsTrue()) return PODVariant(false);
			auto right_result = right->Execute(context);

			return PODVariant(right_result.IsTrue());
		}
	};

	class LogicalExpressionOr : public BinaryExpression {
	public:
		LogicalExpressionOr(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			if (left_result.IsTrue()) return PODVariant(true);
			auto right_result = right->Execute(context);
			return PODVariant(right_result.IsTrue());
		}
	};

	class LogicalExpressionNot : public UnaryExpression {
	public:
		LogicalExpressionNot(BaseExpression* inner_operation_)
			: UnaryExpression(inner_operation_) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto result = inner_operation->Execute(context);
			return !result.IsTrue();
		}
	};
} //end of nodefilter
