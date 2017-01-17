#pragma once

#include "graph\graph.h"
#include "gcpql_query_context.h"

namespace gcpql_query {
	class Runner
	{
	public:
		void SetGraphQuery(GraphQuery* query_) {
            query = std::unique_ptr<GraphQuery>(query_);
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(true);
		}

        const GraphQuery* GetQuery() const {
            return query.get();
        }

	private:
		std::unique_ptr<GraphQuery> query;

	};
}//end of gcpql_query namespace

