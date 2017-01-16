#include <map>
#include "graph_path.h"

#include "src\gcpqlParser\common\disjoint_hash_set.h"

namespace gcpql_query {
bool GraphPath::IsValid() const{
    disjoint_hash_set<std::string> ds;
    for (auto const& node : relations) {
        ds.Add(node->From().GetName());
        ds.Add(node->To().GetName());
    }

    return ds.IsSinglePath();
}
}//end namespace