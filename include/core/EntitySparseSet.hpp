#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

#include "Entity.hpp"

class EntitySparseSet {
public:
    EntitySparseSet() { sparse.resize(MAX_ENTITIES, INVALID_ENTITY); }

    void add(Entity e) {
        assert(e < sparse.size() && "Entity out of range");
        if (has(e)) return;
        sparse[e] = dense.size();
        dense.push_back(e);
    }

    void remove(Entity e) {
        if (!has(e)) return;

        size_t index = sparse[e];
        Entity last = dense.back();
        dense[index] = last;
        sparse[last] = index;
        dense.pop_back();
        sparse[e] = INVALID_ENTITY;
    }

    bool has(Entity e) const { return e < sparse.size() && sparse[e] != INVALID_ENTITY; }
    size_t size() const { return dense.size(); }

    auto begin() const { return dense.begin(); }
    auto end() const { return dense.end(); }

private:
    std::vector<size_t> sparse;  // Entity -> index in dense
    std::vector<Entity> dense;   // Entities dense array
};
