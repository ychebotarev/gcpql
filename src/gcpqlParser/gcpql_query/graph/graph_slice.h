#pragma once

namespace gcpql_query {
    class GraphSlice {
    public:
        void Add(GraphNode* node) {
            collection.push_back(std::unique_ptr<GraphNode>(node));
        }
    private:
        std::vector<std::unique_ptr<GraphNode>> collection;

    };
}