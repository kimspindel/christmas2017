#pragma once
#include <spr/orientation/orientation.hpp>
#include <spr/glm.hpp>

namespace spr
{
glm::vec2 toDirection(Orientation orientation);
Orientation toOrientation(glm::vec2 vec);
bool vec2ContainsOrientation(glm::vec2 vec, Orientation orientation);
}