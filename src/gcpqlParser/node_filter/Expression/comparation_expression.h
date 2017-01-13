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

			if (left_result.Is<double>() || right_result.Is<double>()) {
				auto v1 = left_result.AsDouble();
				auto v2 = right_result.AsDouble();
				return (
					v1 == v2 ||
					std::abs(v1 - v2) < std::abs(std::min(v1, v2))*std::numeric_limits<double>::epsilon());
			}

			auto value_l = left_result.AsLong();
			auto value_r = right_result.AsLong();
			return value_l == value_r;
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

			if (left_result.Is<double>() || right_result.Is<double>()) {
				auto v1 = left_result.AsDouble();
				auto v2 = right_result.AsDouble();
				return !(
					v1 == v2 ||
					std::abs(v1 - v2) < std::abs(std::min(v1, v2))*std::numeric_limits<double>::epsilon());

			}

			return left_result.AsLong() != right_result.AsLong();
		}
	};
}