#pragma once
#include <fea/render2d.hpp>
#include <spr/rendering/rendercontext.hpp>

namespace spr
{
template <typename ExtraData>
class RenderLogic
{
    public:
        RenderLogic(fea::Renderer2D& feaRenderer, ExtraData& data):
            mFeaRenderer(feaRenderer),
            mData(data)
        {
            mData.defaultViewport = feaRenderer.getViewport();
            mData.guiViewport = feaRenderer.getViewport();
        }
        
        void frameStart()
        {
            RenderContext context
            {
                mFeaRenderer,
                mData.screenSize,
            };
        
            mFeaRenderer.clear();
        
            for(auto iter : mData.renderPasses)
            {
                auto preRenderFunction = iter.second.preRenderFunction;
                if(preRenderFunction)
                    preRenderFunction(context, mData);
            }
        
            //setup position and zoom
            mData.worldCamera.setPosition(mData.camera.position);
            mData.worldCamera.setZoom({mData.camera.zoom, mData.camera.zoom});
            mData.defaultViewport.setCamera(mData.worldCamera);
            mData.guiViewport.setCamera(mData.guiCamera);
        }
        
        void update()
        {
            RenderContext context
            {
                mFeaRenderer,
                mData.screenSize,
            };
        
            for(auto iter : mData.renderPasses)
            {
                auto renderFunction = iter.second.renderFunction;
                if(renderFunction)
                    renderFunction(context, mData);
            }
        }
        
        void frameEnd()
        {
            RenderContext context
            {
                mFeaRenderer,
                mData.screenSize,
            };
        
            for(auto iter : mData.renderPasses)
            {
                auto postRenderFunction = iter.second.postRenderFunction;
                if(postRenderFunction)
                    postRenderFunction(context, mData);
            }
        }
        
        void resize(glm::ivec2 newSize)
        {
            for(auto iter : mData.renderPasses)
            {
                auto resizeFunction = iter.second.resizeFunction;
                if(resizeFunction)
                    resizeFunction(newSize, mData);
            }
        
            mData.defaultViewport = fea::Viewport(newSize, {}, {});
            mData.guiViewport = fea::Viewport(newSize, {}, {});
        }
    private:
        fea::Renderer2D& mFeaRenderer;
        ExtraData& mData;
};
}