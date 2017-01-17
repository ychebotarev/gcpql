#pragma once
#include "base_expression.h"

namespace gcpql_query {

	class ConstantExpressionDouble : public BaseExpression {
	public:
		ConstantExpressionDouble(double d) {
			this->value = d;
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(value);
		}

	private:
		double value;
	};

	class ConstantExpressionInteger : public BaseExpression {
	public:
		ConstantExpressionInteger(int i) {
			this->value = i;
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(value);
		}

	private:
		int value;
	};

	class ConstantExpressionIdentifier : public BaseExpression {
	public:
		ConstantExpressionIdentifier(std::string* value_) : value(value_){
		}

		AstVariant Execute(const IQueryContext& context) {
			return context.GetPropertyValue(*value.get());
		}

	private:
		std::unique_ptr<std::string> value;
	};

	class ConstantExpressionString : public BaseExpression {
	public:
		ConstantExpressionString(std::string* value_):value(value_) {
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(value.get());
		}

	private:
		std::unique_ptr<std::string> value;
	};
	
}//end nodefilter