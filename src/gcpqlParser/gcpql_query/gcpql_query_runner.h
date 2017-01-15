#pragma once

#include "graph\graph.h"
#include "gcpql_query_context.h"

namespace gcpql_query {
	class Runner
	{
	public:
		void SetGraphPath(GraphPath* _path) {
			root = std::unique_ptr<GraphPath>(_path);
		}

		AstVariant Execute(const IQueryContext& context) {
			return AstVariant(true);
		}

	private:
		std::unique_ptr<GraphPath> root;

	};
}//end of gcpql_query namespace

