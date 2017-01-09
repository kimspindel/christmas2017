#pragma once
//autogenerated file/ do not edit

#include <dpx/tables.hpp>
#include <memory>
#include <thero/optional.hpp>
#include <fea/rendering/texture.hpp>
#include <vector>
#include <spr/entitystates/stateexecutor.hpp>
#include <fea/rendering/color.hpp>
#include <dpx/tableid.hpp>
#include <string>
#include <spr/physics/collisiontype.hpp>
#include <spr/glm.hpp>
#include <spr/physics/aabb.hpp>
#include <spr/hash/stringhash.hpp>
#include <cstdint>
#include <spr/orientation/orientation.hpp>

#include <spr/physics/collisionexecutor.hpp>
#include <spr/entitystates/statecontext.hpp>
#include <unordered_map>
#include <cstring>
#include <spr/entitystates/duration.hpp>

namespace spr
{
//Four Directional Animation Group Index - Hash index for four directional animation groups
struct FourDirectionalAnimationGroupIndex
{
    StringHash hash;
    dpx::TableId id;
};

using TFourDirectionalAnimationGroupIndex = dpx::DataTable<FourDirectionalAnimationGroupIndex, false>;
}
