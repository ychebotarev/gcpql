#pragma once

#include "graph\graph.h"
#include "gcpql_query_context.h"

namespace gcpql_query {
	class Runner
	{
	public:
		void SetGraphPath(GraphPath* path_) {
			path = std::unique_ptr<GraphPath>(path_);
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(true);
		}

        const GraphPath* GetPath() const {
            return path.get();
        }

	private:
		std::unique_ptr<GraphPath> path;

	};
}//end of gcpql_query namespace

