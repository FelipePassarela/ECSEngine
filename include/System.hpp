#pragma once

#include <cassert>

#include "Entity.hpp"
#include "EntityRegistry.hpp"

class System {
private:
    EntitySparseSet pool;

public:
    virtual ~System() = default;

    virtual void update(float dt) = 0;
    virtual void add(Entity e) { pool.add(e); };
    virtual void remove(Entity e) { pool.remove(e); };
    virtual bool has(Entity e) const { return pool.has(e); }

    // Should only be called when an entity's components change, to keep the pool clean.
    // Never in update() loop.
    virtual bool required(Entity e) = 0;
};
