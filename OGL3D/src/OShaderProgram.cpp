#include "OShaderProgram.h"
#include "glad.h"
#include <fstream>
#include <sstream>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
    m_programId = glCreateProgram();
    attach(desc.vertexShaderFilePath, VertexShader);
    attach(desc.fragmentShaderFilePath, FragmentShader);
    link();
}

OShaderProgram::~OShaderProgram()
{
    for (ui32 i=0; i < 2; i++)
    {
        glDetachShader(m_programId, m_attachedShaders[i]);
        glDeleteShader(m_attachedShaders[i]);
    }
    glDeleteProgram(m_programId);
}

ui32 OShaderProgram::getId()
{
    return m_programId;
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
    std::string shaderCode;
    std::ifstream shaderStream(shaderFilePath);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else
    {  
        return;
    }

    ui32 shaderId = 0;
    if (type == VertexShader)
        shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if (type == FragmentShader)
        shaderId = glCreateShader(GL_FRAGMENT_SHADER);

    auto sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    glAttachShader(m_programId, shaderId);
    m_attachedShaders[type] = shaderId;
}

void OShaderProgram::link()
{
    glLinkProgram(m_programId);
}