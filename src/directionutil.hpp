#pragma once
#include "direction.hpp"
#include <glm.hpp>

glm::vec2 toVec2(Direction direction);
Direction toDirection(glm::vec2 vec);