#pragma once

#include <cstddef>
#include <vector>

#include "Entity.hpp"

// necessary for create an array of ComponentArray in ComponentRegistry
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void onEntityDestroyed(Entity e) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
public:
    ComponentArray<T>() { sparse.resize(MAX_ENTITIES, INVALID_ENTITY); };

    void add(Entity e, const T& component) {
        if (has(e)) return;

        sparse[e] = dense.size();
        dense.push_back(component);
        entities.push_back(e);
    }

    void remove(Entity e) {
        if (!has(e)) return;

        size_t index = sparse[e];
        size_t last = dense.size() - 1;

        dense[index] = dense[last];
        entities[index] = entities[last];
        sparse[entities[index]] = index;

        if (!dense.empty()) {
            dense.pop_back();
            entities.pop_back();
            sparse[e] = INVALID_ENTITY;
        }
    }

    void clear() {
        dense.clear();
        entities.clear();
        std::fill(sparse.begin(), sparse.end(), INVALID_ENTITY);
    }

    void onEntityDestroyed(Entity e) override {
        if (!has(e)) return;
        remove(e);
    }

    bool has(Entity e) const { return e < sparse.size() && sparse[e] != INVALID_ENTITY; }

    // Should check for existence before calling, i.e., compArray.has(e)
    T& getFrom(Entity e) { return dense[sparse[e]]; }

    size_t size() const { return dense.size(); }
    auto begin() const { return dense.begin(); }
    auto end() const { return dense.end(); }

private:
    std::vector<T> dense;
    std::vector<Entity> sparse;
    std::vector<Entity> entities;
};
