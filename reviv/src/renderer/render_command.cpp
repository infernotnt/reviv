#include "render_command.h"

void logMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParams);

void RenderCommand::drawArrays(const Mesh& mesh)
{
    glDrawArrays(GL_TRIANGLES, 0, mesh.m_Vertices.size());
}

void RenderCommand::drawElements(const Mesh& mesh)
{
    glDrawElements(GL_TRIANGLES, mesh.m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void RenderCommand::setClearColor(const Vec4f& color)
{
    glClearColor(color.a[0], color.a[1], color.a[2], color.a[3]);
}

void RenderCommand::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::setViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void RenderCommand::init()
{

#if RV_DEBUG
    glDebugMessageCallback(logMessageCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // enables you too look in the call stack
    //cout << "Running in DEBUG mode" << endl;
    //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

#endif
   
    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_MULTISAMPLE); // for MSAA anti-aliasing

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    RV_ASSERT((nrAttributes >= 10), ""); 

    glEnable(GL_FRAMEBUFFER_SRGB); // for gamma correction
}

void logMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParams)
{
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            RV_ASSERT(false, "[OpenGL Debug HIGH]" << message);
            cout << message << endl;
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            RV_ASSERT(false, "[OpenGL Debug MEDIUM]" << message);
            break;

        case GL_DEBUG_SEVERITY_LOW:
            RV_ASSERT(false, "[OpenGL Debug LOW]" << message);
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            //cout << "[OpenGL Debug NOTIFICATION] " << message << endl;
            break;

        default:
            RV_ASSERT(false, "ERROR: opengl returned unknown debug error SEVERITY");
            break;
    }
}