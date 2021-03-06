#pragma once

#include"shader.h"
#include"model_loader.h"
#include"texture.h"
#include"camera.h"
#include"scene/scene.h"
#include"render_command.h"
#include"framebuffer.h"

class Skybox
{
public:
    Skybox() = default;
    void init(const std::vector<std::string>& filePaths);
    void onUpdate(Framebuffer* pFramebuffer);

    TextureCubeMap textureCubeMap;
    ModelLoader cubeModel;
    Material material;
    Shader shader;
};