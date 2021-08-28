#pragma once

#include"core/mat.h"
#include"renderer/render_command.h"
#include"scene/scene.h"
#include"scene/asset_manager.h"
#include"framebuffer.h"
#include"skybox.h"
#include"core/time.h"
#include"core/application.h"
#include"renderer/deffered.h"
#include"environment.h"

#include"game_stuff/weather.h"


class RenderManager
{
public:
    ~RenderManager() = default;
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;
    
    static void init() { get()->iInit(); }
    static void onUpdate() { get()->iOnUpdate(); }
    static void shutdown() { get()->iShutdown(); }

    static void onEvent(Event* event);
    
    static RenderManager* get()
    {
        static RenderManager instance;
        return &instance;
    }

    Skybox skybox;
    Shader shadowMapShader;

    //Framebuffer screenFramebuffer;
    Framebuffer defaultFramebuffer;
    //Shader screenShader;
    //Shader depthTestShader;

    Shader shaderDefferedBlinnPhong;
    Shader shaderMonochroma;
    Material materialDefferedBlinnPhong; // special material, bind sort of environment stuff actually
    Deffered deffered;

    void bindEnvironmentAndMaterial(Shader* shader, Environment* environment, Material* material);
    void bindEnvironment(Shader* shader, Environment* environment);

private:
    RenderManager() = default;

    void iInit();
    void iOnUpdate();
    void iShutdown();

    void renderSceneToFramebuffer(Framebuffer* pFrameBuffer);

    void shadowMapRenderPass();
    void defferedGeometryRenderPass();
    void defferedLightingRenderPass();
    void defferedMonochromaRenderPass();

    void beginScene();
    void bindEnvironment(const Shader& shader);

    Environment environment;
};