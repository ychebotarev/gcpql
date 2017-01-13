#pragma once
#include <memory>
#include <vector>
#include "base_expression.h"
#include "constants_collection.h"

namespace gcpql_nodefilter {
	class ValueInCollectionFunction : public BaseExpression {
	public:
		ValueInCollectionFunction(
			BaseExpression* value_,
			ConstantsCollection* collection_)
			: value(value_), collection(collection_) {
		}

		~ValueInCollectionFunction() {
		}

		AstVariant Execute(const IFilterContext& context) {

			auto value_result = value->Execute(context);

			for (auto& node : collection->Get()) {
				auto result = node->Execute(context);

				if (value_result.Equal(result))
					return AstVariant(true);
			}
			return AstVariant(false);
		}
	private:
		std::unique_ptr<BaseExpression> value;
		std::unique_ptr<ConstantsCollection> collection;
	};
}
