#pragma once
#include "Oprerequisites.h"
#include "glad.h"
#include <string>

class OTexture
{
public:
    OTexture(GLenum textureTarget, const std::string& fileName);
    ~OTexture();
/*
    //sould be called once to load the texture
    bool Load();

    //must be called at least once for the specific texture unit
    void Bind(GLenum textureUnit);
*/
    GLenum getTarget();
    ui32 getObj();

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    ui32 m_textureObj;
};