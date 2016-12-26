#pragma once
#include <cstdint>
#include "../direction.hpp"
#include <glm.hpp>

struct GameData;

int32_t spawnBall(glm::vec2 position, Direction direction, GameData& data);