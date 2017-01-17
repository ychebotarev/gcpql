#pragma once

#include <memory>
#include <string>

namespace gcpql_query {
	class GraphNode {
	public:
        GraphNode() {
        }

        GraphNode(std::string* type_) : type(type_) {
        }
        
        GraphNode(std::string* type_, std::string* alias_) : type(type_), alias(alias_) {
        }
        
        const std::string& GetNodeName() const {
            return *type.get();
        }

        const std::string& GetName() const {
            return alias ? *alias.get() : *type.get();
        }
    private:
		std::unique_ptr<std::string> type;
        std::unique_ptr<std::string> alias;
    };
}