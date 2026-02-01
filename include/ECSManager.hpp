#pragma once

#include "ComponentRegistry.hpp"
#include "Entity.hpp"
#include "EntityRegistry.hpp"
#include "SystemRegistry.hpp"

class ECSManager {
public:
    ECSManager() { systemRegistry.buildPools(entityRegistry.begin(), entityRegistry.end()); }

    Entity createEntity() { return entityRegistry.create(); }

    void destroyEntity(Entity e) {
        entityRegistry.destroy(e);
        componentRegistry.onEntityDestroyed(e);
        systemRegistry.onEntityDestroyed(e);
    }

    template <typename T>
    void addSystem(const T& system) {
        systemRegistry.add(system);
    }

    template <typename T>
    void addComponent(Entity e, const T& component) {
        componentRegistry.add(e, component);
        systemRegistry.onSignatureChanged(e);
    }

    template <typename T>
    void removeComponent(Entity e) {
        componentRegistry.remove<T>(e);
        systemRegistry.onSignatureChanged(e);
    }

    void update(float dt) { systemRegistry.update(dt); }

private:
    EntityRegistry entityRegistry = EntityRegistry();
    ComponentRegistry componentRegistry = ComponentRegistry();
    SystemRegistry systemRegistry = SystemRegistry();
};
