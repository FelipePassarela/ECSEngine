#pragma once

#include <cassert>
#include <cstddef>
#include <queue>
#include <stdexcept>

#include "Entity.hpp"
#include "EntitySparseSet.hpp"

class EntityRegistry {
public:
    static EntityRegistry& getInstance() {
        static EntityRegistry instance;
        return instance;
    }
    EntityRegistry(const EntityRegistry&) = delete;
    void operator=(const EntityRegistry&) = delete;

    Entity create() {
        if (availableEntities.empty()) {
            throw std::runtime_error("No more entities available");
        }

        Entity e = availableEntities.front();
        availableEntities.pop();
        activesEntities.add(e);
        return e;
    }

    void destroy(Entity e) {
        assert(activesEntities.has(e) && "Entity is not active");
        activesEntities.remove(e);
        availableEntities.push(e);
    }

    bool has(Entity e) const { return activesEntities.has(e); }
    size_t size() const { return activesEntities.size(); }

    auto begin() const { return activesEntities.begin(); }
    auto end() const { return activesEntities.end(); }

private:
    std::queue<Entity> availableEntities;
    EntitySparseSet activesEntities;

    EntityRegistry() {
        for (Entity e = 0; e < MAX_ENTITIES; e++) {
            availableEntities.push(e);
        }
    }
};
