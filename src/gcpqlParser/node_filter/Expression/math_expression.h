#pragma once
#include "base_expression.h"

namespace gcpql_nodefilter {

	class MathExpressionAdd : public BinaryExpression {
	public:
		MathExpressionAdd(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() + right_result.AsDouble();

			return left_result.AsLong() + right_result.AsLong();
		}
	};
	
	class MathExpressionSub : public BinaryExpression {
	public:
		MathExpressionSub(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() - right_result.AsDouble();

			return left_result.AsLong() - right_result.AsLong();
		}
	};
	
	class MathExpressionMul : public BinaryExpression {
	public:
		MathExpressionMul(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() * right_result.AsDouble();

			return left_result.AsLong() * right_result.AsLong();
		}
	};
	
	class MathExpressionDiv : public BinaryExpression {
	public:
		MathExpressionDiv(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			auto divider = right_result.AsDouble();
			if (divider == 0.0) throw std::overflow_error("divide by zero");
			
			return left_result.AsDouble() / divider;
		}
	};

	class MathExpressionDivInt : public BinaryExpression {
	public:
		MathExpressionDivInt(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
			{
				auto divider = right_result.AsDouble();
				if (divider == 0.0) throw std::overflow_error("divide by zero");
				auto result = left_result.AsDouble() / divider;
				return (int)result;
			}

			auto divider = right_result.AsLong();
			if (divider == 0) throw std::overflow_error("divide by zero");
			return left_result.AsLong() / divider;
		}
	};
}

