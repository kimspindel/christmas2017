#pragma once
//autogenerated file/ do not edit

#include <dpx/tables.hpp>
#include <memory>
#include <thero/optional.hpp>
#include <spr/rendering/renderpass.hpp>
#include <fea/rendering/viewport.hpp>
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
//Entity State Machine - State machines that govern the execution of entity states
struct EntityStateMachine
{
    dpx::TableId entityId;
    StringHash currentStateSet;
    dpx::TableId currentState;
    StateContext stateContext;
};

using TEntityStateMachine = dpx::DataTable<EntityStateMachine, false>;
}

