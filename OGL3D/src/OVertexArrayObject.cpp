#include "Oprerequisites.h"
#include "OVertexArrayObject.h"
#include "glad.h"

OVertexArrayObject :: OVertexArrayObject(const OVertexBufferDesc& data)
{
    glGenVertexArrays(1, &m_vertexArrayObjectId);
    glBindVertexArray(m_vertexArrayObjectId);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

    for (ui32 i = 0; i < data.attributesListSize; i++)
    {
        glVertexAttribPointer(
            i,
            data.attributesList[i].numElements,
            GL_FLOAT,
            GL_FALSE,
            data.vertexSize,
            (void*)((i==0)?0: data.attributesList[i-1].numElements* sizeof(f32))
        );
    
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);

    m_vertexBufferData = data;

}

OVertexArrayObject :: ~OVertexArrayObject()
{
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 OVertexArrayObject::getId()
{
    return m_vertexArrayObjectId;
}

ui32 OVertexArrayObject::getVertexBufferSize()
{
    return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize()
{
    return m_vertexBufferData.vertexSize;
}

