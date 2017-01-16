#pragma once

#include <map>

template<class _Elem>
class disjoint_hash_set {
    struct internal_node {
        size_t parent;
        int rank;
    };
private:
    std::map<size_t, internal_node> mappings;
public:

    void Add(const _Elem& str) {
        std::hash<_Elem> hasher;
        auto hs = hasher(str);
        if (mappings.find(hs) != mappings.end()) return;
        mappings.insert(std::pair<size_t, internal_node>(hs, { hs, 0 }));
    }

    bool AreInSameSet(const _Elem& elemX, const _Elem& elemY) {
        std::hash<_Elem> hasher;
        auto hsX = hasher(elemX);
        auto hsY = hasher(elemY);

        internal_node& pX = Find(Find(hsX).parent);
        internal_node& pY = Find(Find(hsY).parent);
        return (pX.parent == pY.parent);
    }

    void Union(const _Elem& elemX, const _Elem& elemY) {
        std::hash<_Elem> hasher;
        auto hsX = hasher(elemX);
        auto hsY = hasher(elemY);

        internal_node& pX = Find(Find(hsX).parent);
        internal_node& pY = Find(Find(hsY).parent);
        if (pX.parent == pY.parent) return;

        if (pX.rank < pY.rank) { pX.parent = pY.parent; }
        else {
            pY.parent = pX.parent;
            if (pY.rank == pX.rank) ++pX.rank;
        }
    }

    bool IsSinglePath() {
        if (!mappings.size()) return true;
        CompressPass(mappings.begin()->first);
        auto top_parent = mappings.begin()->second.parent;
        for (auto const& entity : mappings) {
            CompressPass(entity.first);
            if (entity.second.parent != top_parent) return false;
        }

        return true;
    }

private:
    void CompressPass(size_t key) {
        Find(key);
    }

    internal_node& Find(size_t key) {
        auto parent = mappings.find(key);
        if (parent == mappings.end()) throw std::invalid_argument("key missing");
        internal_node& n = parent->second;
        if (n.parent != key)
            n.parent = Find(n.parent).parent;
        return n;
    }
};
