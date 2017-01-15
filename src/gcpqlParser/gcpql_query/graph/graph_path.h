#pragma once

#include <memory>
#include <string>
#include <vector>

#include "graph_relation.h"

namespace gcpql_query {
    class GraphPath {
    public:
        GraphPath() {
        }

        bool IsValid() {
            return true;
        }

        void Add(GraphRelation* relation) {
            relations.push_back(std::unique_ptr<GraphRelation>(relation));
        }
    private:
        std::vector<std::unique_ptr<GraphRelation>> relations;
    };
}