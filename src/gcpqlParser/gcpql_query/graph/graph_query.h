#pragma once

#include "graph_path.h"
#include "graph_slice.h"
#include "graph_path_filter.h"

namespace gcpql_query {
    class GraphQuery {
    public:
        GraphQuery() {

        }
        void SetGraphSlice(GraphPath* path_) {
        }
        void SetGraphSlice(GraphSlice* slice_) {
            slice = std::unique_ptr<GraphSlice>(slice_);
        }
        void SetGraphPath(GraphPath* path_) {
            path = std::unique_ptr<GraphPath>(path_);
        }
        void SetFilter(GraphPathFilter* filter_) {
            filter = std::unique_ptr<GraphPathFilter>(filter_);
        }

        const GraphSlice* GetSlice() const {
            return slice.get();
        }
        const GraphPath* GetPath() const {
            return path.get();
        }
        const GraphPathFilter* GetFilter() const {
            return filter.get();
        }
    private:
        std::unique_ptr<GraphSlice> slice;
        std::unique_ptr<GraphPath> path;
        std::unique_ptr<GraphPathFilter> filter;

    };
}