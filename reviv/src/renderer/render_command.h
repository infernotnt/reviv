#pragma once

#include"vertex_array.h"
#include"core/mat.h"
#include"renderer/mesh.h"

class RenderCommand
{
public:
    ~RenderCommand() = default;
    RenderCommand(const RenderCommand&) = delete;
    RenderCommand& operator=(const RenderCommand&) = delete;

    static RenderCommand* get()
    {
        static RenderCommand instance;
        return &instance;
    }

    void init();
    void drawArrays(const Mesh& mesh);
    void drawElements(const Mesh& mesh);
    void setClearColor(const Vec4f& color);
    void clear();
    void setViewport(int x, int y, int width, int height);

private:
    RenderCommand() = default;

};