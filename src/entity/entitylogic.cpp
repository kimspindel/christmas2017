#include "entitylogic.hpp"
#include "entityutil.hpp"
#include <gamedata.hpp>
#include <spr/data/entityspriteinstance.hpp>
#include <spr/data/animatedsprite.hpp>
#include <spr/data/fourdirectionalsprite.hpp>

EntityLogic::EntityLogic(GameData& data):
    mData(data)
{
}

void EntityLogic::update()
{
    forEach([&](int32_t id, spr::EntitySpriteInstance& objectSprite)
    {
        int32_t spriteId = objectSprite.spriteId;
        spr::Sprite& sprite = get(spriteId, mData.spr.t<spr::TSprite>());       
        const spr::Position& position = get(objectSprite.entityId, mData.spr.t<spr::TPosition>());       

        sprite.position = position.coordinate + objectSprite.offset;

        if(sprite.type == spr::Sprite::AnimatedSprite)
        {
            spr::AnimatedSprite& animatedSprite = get(spriteId, mData.spr.t<spr::TAnimatedSprite>());
            ++animatedSprite.animationClock;
        }
        else if(sprite.type == spr::Sprite::FourDirectionalSprite)
        {
            const spr::Orientation& orientation = get(objectSprite.entityId, mData.spr.t<spr::TEntityOrientation>()).orientation;
            spr::FourDirectionalSprite& fourDirectionalSprite = get(spriteId, mData.spr.t<spr::TFourDirectionalSprite>());
            fourDirectionalSprite.currentOrientation = orientation;
            ++fourDirectionalSprite.animationClock;
        }

    }, mData.spr.t<spr::TEntitySpriteInstance>());

    forEach([&] (int32_t id, const Health& health)
    {
        if(health.amount <= 0)
            removeEntity(id, mData);
    }, mData.data.t<THealth>());

    forEach([&](int32_t id)
    {
        removeEntityData(id, mData);
    }, mData.entitiesToRemove);

    clear(mData.entitiesToRemove);
}
