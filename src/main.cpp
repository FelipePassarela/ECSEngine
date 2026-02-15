#include <iostream>

#include "../include/ECSManager.hpp"

// ==================== Componentes ====================
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

struct Health {
    int hp;
};

// ==================== Sistemas Simples para Teste ====================

// Sistema que só imprime quando update é chamado
class PrintSystem : public System {
public:
    void update(float dt) override {
        std::cout << "[PrintSystem] Update chamado com dt=" << dt << "\n";
    }

    bool required(Entity e) override {
        return true;  // Aceita todas as entidades
    }
};

class CounterSystem : public System {
public:
    void update(float dt) override {
        updateCount++;
        std::cout << "[CounterSystem] Update #" << updateCount << "\n";
    }

    bool required(Entity e) override {
        return e % 2 == 0;  // Aceita apenas entidades pares
    }

    int getUpdateCount() const { return updateCount; }

private:
    int updateCount = 0;
};

// ==================== Testes ====================
int main() {
    std::cout << "========================================\n";
    std::cout << "       Teste do ECSManager\n";
    std::cout << "========================================\n\n";

    // Criar o ECS Manager
    ECSManager& ecs = ECSManager::getInstance();

    // Registrar sistemas
    std::cout << ">>> Registrando sistemas...\n";
    ecs.addSystem(PrintSystem());
    ecs.addSystem(CounterSystem());
    std::cout << "  Sistemas registrados!\n";

    // Criar entidades
    std::cout << "\n>>> Criando entidades...\n";
    Entity e0 = ecs.createEntity();
    Entity e1 = ecs.createEntity();
    Entity e2 = ecs.createEntity();
    Entity e3 = ecs.createEntity();

    std::cout << "  Criadas entidades: " << e0 << ", " << e1 << ", " << e2 << ", " << e3 << "\n";

    // Adicionar componentes
    std::cout << "\n>>> Adicionando componentes...\n";

    ecs.addComponent(e0, Position{0.0f, 0.0f});
    ecs.addComponent(e0, Velocity{1.0f, 0.5f});
    std::cout << "  Entity " << e0 << ": Position, Velocity\n";

    ecs.addComponent(e1, Position{10.0f, 10.0f});
    ecs.addComponent(e1, Health{100});
    std::cout << "  Entity " << e1 << ": Position, Health\n";

    ecs.addComponent(e2, Position{20.0f, 5.0f});
    ecs.addComponent(e2, Velocity{-1.0f, 0.0f});
    ecs.addComponent(e2, Health{50});
    std::cout << "  Entity " << e2 << ": Position, Velocity, Health\n";

    ecs.addComponent(e3, Health{75});
    std::cout << "  Entity " << e3 << ": Health\n";

    // Simular alguns frames
    std::cout << "\n>>> Simulando 3 frames...\n";
    for (int frame = 1; frame <= 3; frame++) {
        std::cout << "\n--- Frame " << frame << " ---\n";
        ecs.update(0.016f);  // ~60 FPS
    }

    // Testar remoção de componente
    std::cout << "\n>>> Removendo Velocity da Entity " << e0 << "...\n";
    ecs.removeComponent<Velocity>(e0);
    std::cout << "  Componente removido!\n";

    // Mais um frame
    std::cout << "\n--- Frame 4 ---\n";
    ecs.update(0.016f);

    // Testar destruição de entidade
    std::cout << "\n>>> Destruindo Entity " << e1 << "...\n";
    ecs.destroyEntity(e1);
    std::cout << "  Entidade destruida!\n";

    // Frame final
    std::cout << "\n--- Frame 5 ---\n";
    ecs.update(0.016f);

    std::cout << "\n========================================\n";
    std::cout << "       Teste concluido com sucesso!\n";
    std::cout << "========================================\n";

    return 0;
}
