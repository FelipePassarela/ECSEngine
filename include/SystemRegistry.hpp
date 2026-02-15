#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include "System.hpp"

class SystemRegistry {
public:
    static SystemRegistry& getInstance() {
        static SystemRegistry instance;
        return instance;
    }
    SystemRegistry(const SystemRegistry&) = delete;
    void operator=(const SystemRegistry&) = delete;

    template <typename T>
    void add(const T& system) {
        static_assert(std::is_base_of<System, T>::value, "T must derive from System");
        if (has<T>()) return;
        systems.push_back(std::make_unique<T>(system));
    }

    template <typename T>
    bool has() const {
        for (const auto& system : systems) {
            if (dynamic_cast<T*>(system.get()) != nullptr) {
                return true;
            }
        }
        return false;
    }

    template <typename Iterator>
    void buildPools(Iterator entitiesBegin, Iterator entitiesEnd) {
        for (auto& system : systems) {
            for (auto it = entitiesBegin; it != entitiesEnd; ++it) {
                if (system->required(*it)) system->add(*it);
            }
        }
    }

    void update(float dt) {
        for (auto& system : systems) {
            system->update(dt);
        }
    }

    void onEntityDestroyed(Entity e) {
        for (auto& system : systems) {
            system->remove(e);
        }
    }

    void onSignatureChanged(Entity e) {
        for (auto& system : systems) {
            if (system->has(e) && !system->required(e)) {
                system->remove(e);
            } else if (!system->has(e) && system->required(e)) {
                system->add(e);
            }
        }
    }

private:
    std::vector<std::unique_ptr<System>> systems;

    SystemRegistry() = default;
};
