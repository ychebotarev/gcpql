#pragma once
#include "base_expression.h"

namespace gcpql_nodefilter {

	class ConstantExpressionDouble : public BaseExpression {
	public:
		ConstantExpressionDouble(double d) {
			this->value = d;
		}

		PODVariant Execute(const IFilterContext& context) {
			return PODVariant(value);
		}

	private:
		double value;
	};

	class ConstantExpressionInteger : public BaseExpression {
	public:
		ConstantExpressionInteger(int i) {
			this->value = i;
		}

		PODVariant Execute(const IFilterContext& context) {
			return PODVariant(value);
		}

	private:
		int value;
	};

	class ConstantExpressionIdentifier : public BaseExpression {
	public:
		ConstantExpressionIdentifier(const std::string& str) {
			this->value = str;
		}

		PODVariant Execute(const IFilterContext& context) {
			return context.GetProperty(value);
		}

	private:
		std::string value;
	};
}//end nodefilter