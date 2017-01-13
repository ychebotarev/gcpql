#pragma once
#include "base_expression.h"
#include "src\gcpqlParser\node_filter\node_filter_context.h"

namespace gcpql_nodefilter {

	class ComparationExpressionGt : public BinaryExpression 
	{
	public:
		ComparationExpressionGt(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if(left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() > right_result.GetDoubleValue();

			return left_result.GetIntegralValue() > right_result.GetIntegralValue();
		}
	};
	
	class ComparationExpressionGtEq : public BinaryExpression 
	{
	public:
		ComparationExpressionGtEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() >= right_result.GetDoubleValue();

			return left_result.GetIntegralValue() >= right_result.GetIntegralValue();
		}
	};
	
	class ComparationExpressionLt : public BinaryExpression 
	{
	public:
		ComparationExpressionLt(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() < right_result.GetDoubleValue();

			return left_result.GetIntegralValue() < right_result.GetIntegralValue();
		}
	};

	class ComparationExpressionLtEq : public BinaryExpression 
	{
	public:
		ComparationExpressionLtEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() <= right_result.GetDoubleValue();

			return left_result.GetIntegralValue() <= right_result.GetIntegralValue();
		}
	};
	
	class ComparationExpressionEq : public BinaryExpression {
	public:
		ComparationExpressionEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>()) {
				auto value_l = left_result.GetDoubleValue();
				auto value_r = right_result.GetDoubleValue();
				return left_result.GetDoubleValue() == right_result.GetDoubleValue();
			}

			auto value_l = left_result.GetIntegralValue();
			auto value_r = right_result.GetIntegralValue();
			return value_l == value_r;
		}
	};

	class ComparationExpressionNotEq : public BinaryExpression {
	public:
		ComparationExpressionNotEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		PODVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.GetDoubleValue() != right_result.GetDoubleValue();

			return left_result.GetIntegralValue() != right_result.GetIntegralValue();
		}
	};
}