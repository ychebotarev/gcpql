#pragma once

#include "src\gcpqlParser\gcpql_query\filter\base_expression.h"
#include "src\gcpqlParser\gcpql_query\gcpql_query_context.h"

namespace gcpql_query {
    class GraphPathFilter {
    public:
        void SetRootExpression(BaseExpression* _root) {
            root = std::unique_ptr<BaseExpression>(_root);
        }

        AstVariant Execute(const IQueryContext& context) {
            return root->Execute(context);
        }
    private:
        std::unique_ptr<BaseExpression> root;
    };
}