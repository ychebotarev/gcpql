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

        bool IsValid() const;

        void Add(GraphRelation* relation) {
            relations.push_back(std::unique_ptr<GraphRelation>(relation));
        }

        std::string ToString() const{
            std::string path;
            for (const auto& relation : relations)
            {
                if (path.length()) path += ",";
                path += relation->ToString();
            }

            return path;
        }
    private:
        std::vector<std::unique_ptr<GraphRelation>> relations;
    };
}