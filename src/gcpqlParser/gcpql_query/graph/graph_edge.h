#pragma once

#include <memory>
#include <string>

namespace gcpql_query {
    
    class GraphEdge {
    public:
        GraphEdge(std::string* name_) : name(name_) {
        }
        
        const std::string& GetName() const {
            return *name.get();
        }
    private:
        std::unique_ptr<std::string> name;
    };
}