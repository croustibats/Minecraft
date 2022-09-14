#include "Oprerequisites.h"
#include "OVertexArrayObject.h"
#include "glad.h"

OVertexArrayObject :: OVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
    glGenVertexArrays(1, &m_vertexArrayObjectId);
    glBindVertexArray(m_vertexArrayObjectId);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW);

    for (ui32 i = 0; i < vbDesc.attributesListSize; i++)
    {
        glVertexAttribPointer(
            i,
            vbDesc.attributesList[i].numElements,
            GL_FLOAT,
            GL_FALSE,
            vbDesc.vertexSize,
            (void*)((i==0)?0: vbDesc.attributesList[i-1].numElements* sizeof(f32))
        );
    
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);

    m_vertexBufferData = vbDesc;

}

OVertexArrayObject :: OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc):OVertexArrayObject(vbDesc)
{
    glBindVertexArray(m_vertexArrayObjectId);

    glGenBuffers(1, &m_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

OVertexArrayObject :: ~OVertexArrayObject()
{
    glDeleteBuffers(1, &m_elementBufferId);
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

