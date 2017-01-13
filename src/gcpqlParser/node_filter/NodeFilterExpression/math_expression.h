#pragma once
#include "base_expression.h"

namespace gcpql_nodefilter {

	class MathExpressionAdd : public BinaryExpression {
	public:
		MathExpressionAdd(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() + right_result.GetDoubleValue();

			return left_result.GetIntegralValue() + right_result.GetIntegralValue();
		}
	};
	
	class MathExpressionSub : public BinaryExpression {
	public:
		MathExpressionSub(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() - right_result.GetDoubleValue();

			return left_result.GetIntegralValue() - right_result.GetIntegralValue();
		}
	};
	
	class MathExpressionMul : public BinaryExpression {
	public:
		MathExpressionMul(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() * right_result.GetDoubleValue();

			return left_result.GetIntegralValue() * right_result.GetIntegralValue();
		}
	};
	
	class MathExpressionDiv : public BinaryExpression {
	public:
		MathExpressionDiv(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			auto divider = right_result.GetDoubleValue();
			if (divider == 0.0) throw std::overflow_error("divide by zero");
			
			return left_result.GetDoubleValue() / divider;
		}
	};

	class MathExpressionDivInt : public BinaryExpression {
	public:
		MathExpressionDivInt(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}
		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
			{
				auto divider = right_result.GetDoubleValue();
				if (divider == 0.0) throw std::overflow_error("divide by zero");
				auto result = left_result.GetDoubleValue() / divider;
				return (int)result;
			}

			auto divider = right_result.GetIntegralValue();
			if (divider == 0) throw std::overflow_error("divide by zero");
			return left_result.GetIntegralValue() / divider;
		}
	};
}

