cmake_minimum_required(VERSION 3.16)
project(myECS VERSION 1.0.0 LANGUAGES CXX)

# Configurações do padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opções de compilação
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Flags de warning
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Biblioteca header-only do ECS
add_library(ecs INTERFACE)
target_include_directories(ecs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executável principal
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ecs)

# Teste do ECSManager
add_executable(test_ecs_manager src/test_ecs_manager.cpp)
target_link_libraries(test_ecs_manager PRIVATE ecs)

# Opção para build de release otimizado
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-O3 -march=native)
    endif()
endif()
