#include "Oprerequisites.h"
#include "OVec4.h"
#include "ORect.h"

class OGraphicsEngine
{
public:
    OGraphicsEngine();
    ~OGraphicsEngine();
public:
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc);
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc & ibDesc);
    OUniformBufferPtr createUniformBuffer(const OUniformBufferDesc& desc);
    OShaderProgramPtr createShaderProgram(const OShaderProgramDesc & desc);
public:
    void clear(const OVec4& color);
    void setFaceCulling(const OCullType& type);
    void setWindingOrder(const OWindingOrder& order);
    void setViewport(const ORect& size);
    void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
    void setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot);
    void setShaderProgram(const OShaderProgramPtr& program);
    void drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset);
    void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount);
};