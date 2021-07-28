#pragma once

#include"rv_pch.hpp"

#include"core/mat.h"
#include"shader.h"
#include"buffer.h"
#include"texture.h"

extern unsigned int ShaderDataTypeSize(ShaderDataType type);

struct MaterialHelpingStruct
{
    MaterialHelpingStruct() : ptr(nullptr) {}
    void* ptr = nullptr;
    ShaderDataType type;

    MaterialHelpingStruct(const MaterialHelpingStruct&) = delete;
    MaterialHelpingStruct& operator=(const MaterialHelpingStruct&) = delete;

    bool operator==(const MaterialHelpingStruct& other) const = delete;
    bool operator!=(const MaterialHelpingStruct& other) const = delete;

};

class Material
{
public:
    Material() = default;
    ~Material();
    Material(const Material& other) = delete; // can be implemented
    Material& operator=(const Material& other) = delete; // can be implemented

    Material(const Shader* pShader)
        : pShader(pShader), pTextures(5) { map.clear(); }

    void setShader(Shader* inShader);
    void bindShader();
    void bind() const;
    void set(const std::string& uniformName, const Mat4& mat4);
    void set(const std::string& uniformName, const Vec4f& vec4f);
    void set(const std::string& uniformName, const Vec3f& vec3f);
    void set(const std::string& uniformName, int n);
    void set(const std::string& uniformName, float n);
    void set(const std::string& uniformName, double n);

    const Shader* pShader = nullptr;
    std::unordered_map <std::string, MaterialHelpingStruct> map;
    stls::StableVector<const Texture*> pTextures;

    void addTexture(const Texture& texture);
};

void log(const Material& material);
void logSpecificUniform(const Material& material, const std::string& uniformName);