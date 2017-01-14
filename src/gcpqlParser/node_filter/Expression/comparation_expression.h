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

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);
			
			if (!left_result.IsCompatible(right_result)
				|| left_result.IsStringType()
				|| right_result.IsStringType()) return false;

			if(left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() > right_result.AsDouble();

			return left_result.AsLong() > right_result.AsLong();
		}
	};
	
	class ComparationExpressionGtEq : public BinaryExpression 
	{
	public:
		ComparationExpressionGtEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (!left_result.IsCompatible(right_result)
				|| left_result.IsStringType()
				|| right_result.IsStringType()) return false;

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() >= right_result.AsDouble();

			return left_result.AsLong() >= right_result.AsLong();
		}
	};
	
	class ComparationExpressionLt : public BinaryExpression 
	{
	public:
		ComparationExpressionLt(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (!left_result.IsCompatible(right_result)
				|| left_result.IsStringType()
				|| right_result.IsStringType()) return false;

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() < right_result.AsDouble();

			return left_result.AsLong() < right_result.AsLong();
		}
	};

	class ComparationExpressionLtEq : public BinaryExpression 
	{
	public:
		ComparationExpressionLtEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			if (!left_result.IsCompatible(right_result)
				|| left_result.IsStringType()
				|| right_result.IsStringType()) return false;

			if (left_result.Is<double>() || right_result.Is<double>())
				return left_result.AsDouble() <= right_result.AsDouble();

			return left_result.AsLong() <= right_result.AsLong();
		}
	};
	
	class ComparationExpressionEq : public BinaryExpression {
	public:
		ComparationExpressionEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			return left_result.Equal(right_result);
		}
	};

	class ComparationExpressionNotEq : public BinaryExpression {
	public:
		ComparationExpressionNotEq(BaseExpression* left, BaseExpression* right)
			: BinaryExpression(left, right) {
		}

		AstVariant Execute(const IFilterContext& context) {
			auto left_result = left->Execute(context);
			auto right_result = right->Execute(context);

			return !left_result.Equal(right_result);
		}
	};
}