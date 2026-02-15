#pragma once

#include <cstddef>
#include <limits>

using Entity = size_t;

constexpr Entity INVALID_ENTITY = std::numeric_limits<Entity>::max();
constexpr size_t MAX_ENTITIES = 10000;
