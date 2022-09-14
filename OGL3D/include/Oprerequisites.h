#pragma once

#include <memory>

class OVertexArrayObject;
class OUniformBuffer;
class OShaderProgram;

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct OVertexAttribute
{
    ui32 numElements = 0;
};

struct OVertexBufferDesc
{
    void* verticesList = nullptr;
    ui32 vertexSize = 0;
    ui32 listSize = 0;

    OVertexAttribute* attributesList = nullptr;
    ui32 attributesListSize = 0;
};

struct OIndexBufferDesc
{
    void* indicesList = nullptr;
    ui32 listSize = 0;
};

struct OShaderProgramDesc
{
    const wchar_t* vertexShaderFilePath;
    const wchar_t* fragmentShaderFilePath;
};

struct OUniformBufferDesc
{
    ui32 size = 0;
};

enum OTriangleType
{
    TriangleList = 0,
    TriangleStrip
};

enum OCullType
{
    BackFace = 0,
    FrontFace,
    Both
};

enum OWindingOrder
{
    ClockWise = 0,
    CounterClockWise
};

enum OShaderType
{
    VertexShader = 0,
    FragmentShader
};