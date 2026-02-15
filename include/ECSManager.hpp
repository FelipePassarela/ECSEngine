#pragma once

#include "core/ComponentRegistry.hpp"
#include "core/Entity.hpp"
#include "core/EntityRegistry.hpp"
#include "core/SystemRegistry.hpp"

class ECSManager {
public:
    static ECSManager& getInstance() {
        static ECSManager instance;
        return instance;
    }
    ECSManager(const ECSManager&) = delete;
    void operator=(const ECSManager&) = delete;

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
    EntityRegistry& entityRegistry = EntityRegistry::getInstance();
    ComponentRegistry& componentRegistry = ComponentRegistry::getInstance();
    SystemRegistry& systemRegistry = SystemRegistry::getInstance();

    ECSManager() { systemRegistry.buildPools(entityRegistry.begin(), entityRegistry.end()); }
};
