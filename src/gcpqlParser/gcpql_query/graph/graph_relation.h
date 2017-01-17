#pragma once

#include <memory>
#include <string>

#include "graph_node.h"

namespace gcpql_query {

    class GraphRelation {
    public:
        GraphRelation(GraphNode* from_, GraphNode *to_, GraphNode* edge_)
            : from(from_), to(to_),  edge(edge_){

        }
        GraphRelation(GraphNode* from_, GraphNode *to_)
            : from(from_), to(to_) {
        }

        std::string ToString() const;

        const GraphNode& From() const {
            return *from;
        }
        
        const GraphNode& To() const {
            return *to;
        }
    private:
        std::unique_ptr<GraphNode> from;
        std::unique_ptr<GraphNode> to;
        std::unique_ptr<GraphNode> edge;
    };
}