#include "graph_relation.h"

#include <sstream>

namespace gcpql_query {
    std::string GraphRelation::ToString() const {
        std::stringstream fmt;
        fmt << "(" << (from ? from->GetName() : "*") << "," << (to ? to->GetName() : "*");
        if (edge)
            fmt << "," << edge->GetName();
        fmt << ")";
        return fmt.str();
    }
}
