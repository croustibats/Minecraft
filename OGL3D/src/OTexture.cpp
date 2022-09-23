#include "stb_image.h"
#include "OTexture.h"
#include <iostream>

OTexture::OTexture(GLenum textureTarget, const std::string& fileName)
{
    m_textureTarget = textureTarget;
    m_fileName = fileName;


    int widthImg, heightImg, numColCh;
    //"C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\pop_cat.png"
    unsigned char* data = stbi_load(m_fileName.c_str(), &widthImg, &heightImg, &numColCh, 0);

    if (data)
    {
        std::cout << "Success to load texture" << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    glGenTextures(1, &m_textureObj);
    // "Lie" la nouvelle texture : toutes les fonctions agissant sur les textures suivantes vont modifier cette texture
    glBindTexture(m_textureTarget, m_textureObj);
    // Donne l'image à OpenGL
    if (m_textureTarget == GL_TEXTURE_2D)
    {
        glTexImage2D(m_textureTarget, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "can't load texture from " << m_fileName.c_str() << std::abort;
        exit(0);
    }

    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(m_textureTarget, 0);

    stbi_image_free(data);
}

OTexture::~OTexture()
{

}

GLenum OTexture::getTarget()
{
    return m_textureTarget;
}

ui32 OTexture::getObj()
{
    return m_textureObj;
}