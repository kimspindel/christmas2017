//autogenerated file/ do not edit
#include "tables.hpp"

#include <spr/data/entitystatemachine.hpp>
#include <spr/data/entitystate.hpp>
#include <spr/data/entitystateindex.hpp>
#include <spr/data/entityorientation.hpp>
#include <spr/data/position.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/texture.hpp>
#include <spr/data/textureindex.hpp>
#include <spr/data/spriteanimation.hpp>
#include <spr/data/spriteanimationindex.hpp>
#include <spr/data/fourdirectionalanimationgroup.hpp>
#include <spr/data/fourdirectionalanimationgroupindex.hpp>
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/sprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/entitydirection.hpp>

namespace spr
{
void instantiateTables(Tables& tables)
{
    tables.tEntityStateMachine = std::make_unique<TEntityStateMachine>("Entity State Machine", "State machines that govern the execution of entity states");
    tables.tEntityState = std::make_unique<TEntityState>("Entity State", "A state that an entity can attain");
    tables.tEntityStateIndex = std::make_unique<TEntityStateIndex>("Entity State Set", "Index of entity states that store which sets and such they belong to");
    tables.tEntityOrientation = std::make_unique<TEntityOrientation>("Orientation", "How an entity is turned");
    tables.tPosition = std::make_unique<TPosition>("Position", "Entity positions in the world");
    tables.tHitbox = std::make_unique<THitbox>("Hitbox", "The collision size of an entity");
    tables.tEntityCollider = std::make_unique<TEntityCollider>("Entity Collider", "Data for entities that collide with other entities");
    tables.tTexture = std::make_unique<TTexture>("Texture", "Texture resource");
    tables.tTextureIndex = std::make_unique<TTextureIndex>("Texture Index", "Index of all textures using hashes");
    tables.tSpriteAnimation = std::make_unique<TSpriteAnimation>("Sprite Animation", "Animation data for a sprite");
    tables.tSpriteAnimationIndex = std::make_unique<TSpriteAnimationIndex>("Sprite Animation Index", "Hash index for animations");
    tables.tFourDirectionalAnimationGroup = std::make_unique<TFourDirectionalAnimationGroup>("Four Directional Animation Group", "A four directional grouping of animations");
    tables.tFourDirectionalAnimationGroupIndex = std::make_unique<TFourDirectionalAnimationGroupIndex>("Four Directional Animation Group Index", "Hash index for four directional animation groups");
    tables.tEntitySpriteInstance = std::make_unique<TEntitySpriteInstance>("Entity Sprite Instance", "Relationship describing a sprite instance that belongs to an entity");
    tables.tSprite = std::make_unique<TSprite>("Sprite", "2D Image in the gameworld");
    tables.tFourDirectionalSprite = std::make_unique<TFourDirectionalSprite>("Four Directional Sprite", "A sprite that is animatable in four directions");
    tables.tAnimatedSprite = std::make_unique<TAnimatedSprite>("Animated Sprite", "A sprite with animation capabilities");
    tables.tEntityDirection = std::make_unique<TEntityDirection>("Entity Direction", "The logical direction of an entity");
}
}