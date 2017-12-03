#include "renderlogic.hpp"
#include <imgui/imgui.h>
#include <gamedata.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spr/debug/debugrenderer.hpp>
#include <spr/data/gltexture.hpp>
#include <spr/data/shaderprogram.hpp>
#include <spr/data/camera.hpp>
#include <spr/data/viewport.hpp>
#include <spr/gl/shader.hpp>
#include <spr/gl/gl.hpp>
#include <spr/gl/viewport.hpp>
#include <spr/camera/camera.hpp>
#include <spr/gl/texture.hpp>

RenderLogic::RenderLogic(GameData& data):
    mData(data),
    mSpriteRenderer(mData.spr),
    mTextRenderer(mData.spr),
    mImguiRenderer(mData.spr)
{
    //setup cameras and views
    mData.mainViewport = insert(spr::Viewport
    {
        {0, 0},
        {1366, 768},
    }, *mData.spr.tViewport).id;
    mData.guiCamera = insert(spr::Camera
    {
        {0.0f, 0.0f, 0.0f},
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::mat4(1.0f),

    }, *mData.spr.tCamera).id;
    mData.worldCamera = insert(spr::Camera
    {
        {0.0f, 0.0f, 0.0f},
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::mat4(1.0f),
    }, *mData.spr.tCamera).id;

    //initialize our global debug renderer
    spr::DRen::initialize(mData.worldCamera, data.spr);

    //setup our shader
    std::string vertex = 
R"(
precision mediump float;

uniform mat4 viewProjection;

attribute vec4 position; //will be compatible with vec2 and vec3 attributes. extended to vec4: (0, 0, 0, 1) for missing components
attribute vec2 texCoord;
attribute vec4 color;

varying vec2 vTex;
varying vec4 vColor;

void main()
{
    gl_Position = viewProjection * position;
    vTex = texCoord;
	vColor = color;
}
)";

    std::string fragment = 
R"(
precision mediump float;

uniform sampler2D texture;

varying vec2 vTex;
varying vec4 vColor;

void main()
{
    gl_FragColor = texture2D(texture, vTex) * vColor;
}
)";
    mData.mainShader = createShaderProgram(vertex, fragment, {{"position", 0}, {"texCoord", 1}, {"color", 2}}, mData.spr);

    //setup gl values
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderLogic::frameStart(spr::Color clearColor)
{
    glClearColor(clearColor.rAsFloat(), clearColor.gAsFloat(), clearColor.bAsFloat(), clearColor.aAsFloat());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    spr::gl::setViewport(mData.mainViewport, mData.spr);

    mImguiRenderer.frameStart();
}

void RenderLogic::renderFrame()
{
    //all sprites
    mSpriteRenderer.render();
    //all texts
    mTextRenderer.render();
    //draw all debug primitives
    spr::DRen::render(true, mData.mainViewport, mData.worldCamera, mData.mainShader);
    //imgui
    mImguiRenderer.renderFrame(mData.mainViewport, mData.guiCamera, mData.mainShader);
}

void RenderLogic::resizeWindow(glm::ivec2 iSize)
{
    glm::vec2 size = static_cast<glm::vec2>(iSize);
    glm::vec2 halfSize = size / 2.0f;
    float zoom = 0.5f;
    glm::vec2 worldHalfSize = halfSize * zoom;

    spr::gl::resizeViewport(mData.screenSize, mData.mainViewport, mData.spr);

    spr::Camera& worldCamera = get(mData.worldCamera, *mData.spr.tCamera);
    glm::mat4 worldProjection = glm::ortho(-worldHalfSize.x, worldHalfSize.x, worldHalfSize.y, -worldHalfSize.y, -100.0f, 100.0f);
    worldCamera.projection = worldProjection;

    spr::Camera& guiCamera = get(mData.guiCamera, *mData.spr.tCamera);
    glm::mat4 guiProjection = glm::ortho(0.0f, size.x, size.y, 0.0f, -100.0f, 100.0f);
    guiCamera.projection = guiProjection;
}
