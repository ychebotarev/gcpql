#pragma once

#include <memory>
#include <string>

namespace gcpql_query {
    
    class GraphEdge {
    public:
        GraphEdge(std::string* type_) : type(type_) {

        }
    private:
        std::unique_ptr<std::string> type;
    };
}