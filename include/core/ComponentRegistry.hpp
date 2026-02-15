#pragma once

#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "ComponentArray.hpp"
#include "Entity.hpp"

class ComponentRegistry {
public:
    static ComponentRegistry& getInstance() {
        static ComponentRegistry instance;
        return instance;
    }
    ComponentRegistry(const ComponentRegistry&) = delete;
    void operator=(const ComponentRegistry&) = delete;

    template <typename T>
    void add(Entity e, const T& component) {
        if (!hasArray<T>()) {
            // TODO: make the constructor paramater a global constant
            arrays[typeid(T)] = std::make_unique<ComponentArray<T>>();
        }
        ComponentArray<T>* array = getArray<T>();
        array->add(e, component);
    }

    template <typename T>
    T* getComponent(Entity e) const {
        if (!hasArray<T>()) return nullptr;
        return getArray<T>()->getFrom(e);
    }

    template <typename T>
    void remove(Entity e) {
        getArray<T>()->remove(e);
    }

    template <typename T>
    ComponentArray<T>* getArray() const {
        assert(hasArray<T>() && "Component not registered");
        return static_cast<ComponentArray<T>*>(arrays.at(typeid(T)).get());
    }

    void onEntityDestroyed(Entity e) {
        for (auto const& pair : arrays) {
            auto const& array = pair.second;
            array->onEntityDestroyed(e);
        }
    }

    template <typename T>
    bool has(Entity e) const {
        if (!hasArray<T>()) return false;
        return getArray<T>()->has(e);
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> arrays;

    template <typename T>
    bool hasArray() const {
        return arrays.find(typeid(T)) != arrays.end();
    }

    ComponentRegistry() = default;
};
