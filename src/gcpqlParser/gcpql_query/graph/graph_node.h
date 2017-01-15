#pragma once

#include <memory>
#include <string>

namespace gcpql_query {
	class GraphNode {
	public:
        GraphNode(std::string* type_) : type(type_) {

        }
        GraphNode(std::string* type_, std::string* alias_) : type(type_), alias(alias_) {

        }
    private:
		std::unique_ptr<std::string> type;
        std::unique_ptr<std::string> alias;
    };
}