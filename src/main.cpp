#include <iostream>

#include "../include/ComponentRegistry.hpp"

// Componentes de teste
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

int main() {
    ComponentRegistry registry;

    // Criar algumas entidades
    Entity e1 = 0;
    Entity e2 = 1;
    Entity e3 = 2;

    // Adicionar componentes
    registry.add(e1, Position{10.0f, 20.0f});
    registry.add(e1, Velocity{1.0f, 2.0f});

    registry.add(e2, Position{30.0f, 40.0f});

    registry.add(e3, Position{50.0f, 60.0f});
    registry.add(e3, Velocity{3.0f, 4.0f});

    // Testar se os componentes foram adicionados
    std::cout << "=== Teste de ComponentRegistry ===" << std::endl;

    auto* posArray = registry.getArray<Position>();
    auto* velArray = registry.getArray<Velocity>();

    std::cout << "Entity 1 tem Position? " << (posArray->has(e1) ? "Sim" : "Nao") << std::endl;
    std::cout << "Entity 1 tem Velocity? " << (velArray->has(e1) ? "Sim" : "Nao") << std::endl;
    std::cout << "Entity 2 tem Position? " << (posArray->has(e2) ? "Sim" : "Nao") << std::endl;
    std::cout << "Entity 2 tem Velocity? " << (velArray->has(e2) ? "Sim" : "Nao") << std::endl;

    // Testar remoção
    std::cout << "\n=== Removendo Velocity de Entity 1 ===" << std::endl;
    registry.remove<Velocity>(e1);
    std::cout << "Entity 1 tem Velocity? " << (velArray->has(e1) ? "Sim" : "Nao") << std::endl;

    // Testar onEntityDestroyed
    std::cout << "\n=== Destruindo Entity 3 ===" << std::endl;
    registry.onEntityDestroyed(e3);
    std::cout << "Entity 3 tem Position? " << (posArray->has(e3) ? "Sim" : "Nao") << std::endl;
    std::cout << "Entity 3 tem Velocity? " << (velArray->has(e3) ? "Sim" : "Nao") << std::endl;

    std::cout << "\nTodos os testes concluidos!" << std::endl;
    return 0;
}
