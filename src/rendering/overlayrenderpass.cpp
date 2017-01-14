#include "overlayrenderpass.hpp"
#include <spr/data/view.hpp>
#include <spr/rendering/rendercontext.hpp>
#include <spr/rendering/drawables/imguidrawable.hpp>
#include <gamedata.hpp>
#include "../land/chunkutil.hpp"
#include "../land/goodness.hpp"
#include "../resources/textureutil.hpp"
#include <imgui.h>

spr::RenderPass createOverlayRenderPass(GameData& data)
{
    return
    {
        spr::AllocateFunction([&](fea::Renderer2D&)
        {
            data.effectOverlayData.noiseAnimation = {{0,0}, {32, 32}, 4, 4};
            data.effectOverlayData.sinCounter = 0;
            data.effectOverlayData.overlayTarget.create({2048, 2048});
            data.effectOverlayData.overlayQuad.setSize({2048, 2048});
            data.effectOverlayData.overlayQuad.setTexture(data.effectOverlayData.overlayTarget.getTexture());
            data.effectOverlayData.overlayQuad.setVFlip(true);
            data.overlayView = insert(spr::View{fea::Viewport({2048, 2048}, {}, fea::Camera{})}, *data.spr.tView).id;
            data.effectOverlayData.noiseOverlay.setSize({130000.0f, 130000.0f});
            data.effectOverlayData.noiseOverlay.setPosition(-data.effectOverlayData.noiseOverlay.getSize() / 2.0f);
            data.effectOverlayData.noiseOverlay.setTexture(getFeaTexture(data.noiseTexture, data.spr));
            data.effectOverlayData.noiseOverlay.setAnimation(data.effectOverlayData.noiseAnimation);
            data.effectOverlayData.noiseOverlay.setTileSize(glm::ivec2{64, 64});
            data.effectOverlayData.noiseOverlay.setParallax({0.0f, 0.0f});
            data.effectOverlayData.fogOverlay.setSize({130000.0f, 130000.0f});
            data.effectOverlayData.fogOverlay.setPosition(-data.effectOverlayData.fogOverlay.getSize() / 2.0f);
            data.effectOverlayData.fogOverlay.setTexture(getFeaTexture(data.fogTexture, data.spr));
            data.effectOverlayData.fogOverlay.setTileSize(glm::ivec2{256, 256});
            data.effectOverlayData.fogOverlay.setScrollSpeed({0.00001f, 0.0f});
            data.effectOverlayData.fogOverlay.setParallax({0.1f, 0.1f});
        }),
        spr::PreRenderFunction([&](spr::RenderContext& context)
        {
            context.renderer.clear(data.effectOverlayData.overlayTarget, fea::Color::Transparent);

            glm::ivec2 cameraTile = worldToTile(data.camera.position);
            glm::ivec2 cameraChunk = tileToChunk(cameraTile);
            int32_t goodnessAmount = data.worldChunks.at(cameraChunk).tiles[tileIndex(tileToChunkTile(cameraTile))].goodness;
            GoodnessLevel goodnessLevel = goodnessAmountLevel(goodnessAmount);
            int32_t evilAmount = goodnessLevelAmount(GoodnessLevel::Evil, goodnessAmount);
            int32_t dyingAmount = goodnessLevelAmount(GoodnessLevel::Dying, goodnessAmount);
            int32_t corruptAmount = goodnessLevelAmount(GoodnessLevel::Corrupt, goodnessAmount);
            int32_t goodAmount = goodnessLevelAmount(GoodnessLevel::Good, goodnessAmount);

            data.effectOverlayData.sinCounter += 4000;
            if(data.effectOverlayData.sinCounter > 314159)
                data.effectOverlayData.sinCounter = 0;

            float sinInput = data.effectOverlayData.sinCounter / 100000.0f;
            float sinOut = std::sin(sinInput);
            data.effectOverlayData.noiseOverlay.setColor({static_cast<int32_t>(255 * std::fabs(sinOut)), 0, 0, 255});
            data.effectOverlayData.noiseOverlay.setOpacity(std::max(0.0f, evilAmount / 100.0f - 0.15f));
            data.effectOverlayData.fogOverlay.setOpacity(std::max(0.0f, dyingAmount / 100.0f - 0.15f));

            fea::Camera& overlayCamera = get(data.overlayView, *data.spr.tView).viewport.getCamera();
            overlayCamera.setPosition(data.camera.position);// - glm::ivec2(-342, 0));
            overlayCamera.setZoom({1, data.camera.zoom});
        }),
        spr::RenderFunction([&](spr::RenderContext& context)
        {
            context.renderer.render(data.effectOverlayData.fogOverlay);
            context.renderer.render(data.effectOverlayData.noiseOverlay);
            data.effectOverlayData.fogOverlay.tick();
            data.effectOverlayData.noiseOverlay.tick();
           
            fea::Viewport& overlayViewport = get(data.overlayView, *data.spr.tView).viewport; 
            fea::Viewport& worldViewport = get(data.worldView, *data.spr.tView).viewport; 
            
            context.renderer.setViewport(overlayViewport);
            //overlay stuff
            for(auto& overlays : data.chunksInView)
            {
                context.renderer.setBlendMode(fea::ADD);
                context.renderer.render(overlays.second.overlayQuad, data.effectOverlayData.overlayTarget);
            }
            
            context.renderer.setViewport(worldViewport);
            data.effectOverlayData.overlayQuad.setPosition(data.camera.position - glm::ivec2(1024.0f, 1024.0f));
            context.renderer.setBlendMode(fea::MULTIPLY);
            context.renderer.render(data.effectOverlayData.overlayQuad);
            context.renderer.setBlendMode(fea::ALPHA);

        }),
        spr::ResizeFunction([](glm::ivec2 newSize)
        {

        }),
        spr::PostRenderFunction(nullptr),
        //deallocate gui
        spr::DeallocateFunction(nullptr),
    };
}
