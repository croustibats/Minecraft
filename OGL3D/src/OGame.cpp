#include "OGame.h"
#include "Owindow.h"
#include "OGraphicsEngine.h"
#include "OVertexArrayObject.h"
#include "OShaderProgram.h"
#include "OUniformBuffer.h"
#include "OTexture.h"
#include "OMat4.h"
#include "OVec3.h"
#include "OVec2.h"
#include "glad_wgl.h"
#include "glad.h"
#include "stb_image.h"
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <iostream>

struct UniformData
{
    OMat4 world;
    OMat4 projection;
};

struct Vertex
{
    OVec3 position;
    OVec2 texcoord;
};

OGame::OGame()
{
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>();

    m_display->makeCurrentContext();

    m_graphicsEngine->setViewport(m_display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{

    OVec3 positionsList[] = 
    {   
        //front face
        OVec3(-0.5f, -0.5f, -0.5f),
        OVec3(-0.5f, 0.5f, -0.5f),
        OVec3(0.5f, 0.5f, -0.5f),
        OVec3(0.5f, -0.5f, -0.5f),

        //back face
        OVec3(0.5f, -0.5f, 0.5f),
        OVec3(0.5f, 0.5f, 0.5f),
        OVec3(-0.5f, 0.5f, 0.5f),
        OVec3(-0.5f, -0.5f, 0.5f),

    };

    OVec2 texcoordsList[] = 
    {
        OVec2(0.0f,0.0f), // bottom left
        OVec2(0.0f,1.0f), // top left
        OVec2(1.0f,0.0f), // bottom right
        OVec2(1.0f,1.0f) // top right
    };


    Vertex verticesList[] = 
    {
        //front face
        { positionsList[0], texcoordsList[1] },
        { positionsList[1], texcoordsList[0] },
        { positionsList[2], texcoordsList[2] },
        { positionsList[3], texcoordsList[3] },

        //back face
        { positionsList[4], texcoordsList[1] },
        { positionsList[5], texcoordsList[0] },
        { positionsList[6], texcoordsList[2] },
        { positionsList[7], texcoordsList[3] },

        //top face
        { positionsList[1], texcoordsList[1] },
        { positionsList[6], texcoordsList[0] },
        { positionsList[5], texcoordsList[2] },
        { positionsList[2], texcoordsList[3] },

        //bottom face
        { positionsList[7], texcoordsList[1] },
        { positionsList[0], texcoordsList[0] },
        { positionsList[3], texcoordsList[2] },
        { positionsList[4], texcoordsList[3] },

        //right face
        { positionsList[3], texcoordsList[1] },
        { positionsList[2], texcoordsList[0] },
        { positionsList[5], texcoordsList[2] },
        { positionsList[4], texcoordsList[3] },

        //left face
        { positionsList[7], texcoordsList[1] },
        { positionsList[6], texcoordsList[0] },
        { positionsList[1], texcoordsList[2] },
        { positionsList[0], texcoordsList[3] },
    };

    ui32 indicesList[] = 
    {
        //front
        0,1,2,
        2,3,0,

        //back
        4,5,6,
        6,7,4,

        //top
        8,9,10,
        10,11,8,

        //bottom
        12,13,14,
        14,15,12,

        //right
        16,17,18,
        18,19,16,

        //left
        20,21,22,
        22,23,20

    };
/*
    const f32 polygonVertices[] = {
        -0.5f,-0.5f,0.0f,
        0    ,1    ,0   ,

        -0.5f, 0.5f, 0.0f,
        0    ,0    ,1   ,

        0.5f, -0.5f, 0.0f,
        1    ,0    ,0   ,

        0.5f, 0.5f, 0.0f,
        1    ,1    ,0   ,
    };
*/
    OVertexAttribute attribsList[] = {
        sizeof(OVec3)/sizeof(f32), //position
        sizeof(OVec2)/sizeof(f32) //texcoord
    };

    m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
        {
            (void*)verticesList,
            sizeof(Vertex),
            sizeof(verticesList)/sizeof(Vertex),


            attribsList,
            sizeof(attribsList)/sizeof(OVertexAttribute)
        },

        {
            (void*) indicesList,
            sizeof(indicesList)
        }
    );

    m_uniform = m_graphicsEngine->createUniformBuffer({
        sizeof(UniformData)
        });

    m_shader = m_graphicsEngine->createShaderProgram(
        {
            L"C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\OGL3D\\src\\BasicShader.vert",
            L"C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\OGL3D\\src\\BasicShader.frag"
        });
    
    m_shader->setUniformBufferSlot("UniformData", 0);

    //Texture
    m_texture = m_graphicsEngine->createTexture(GL_TEXTURE_2D, "C:\\Users\\Baptiste Cournault\\Documents\\dev\\Minecraft\\pop_cat.png");

}
void OGame::onUpdate()
{
    //Texture 
    //ui32 gSamplerLocation;
    //m_texture->bindTexture(GL_TEXTURE0);
    //glUniform1i(gSamplerLocation, 0);
    //m_graphicsEngine->bindTexture(m_texture, GL_TEXTURE0);

    //computing delta time

    auto currentTime = std::chrono::system_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>();
    if (m_previousTime.time_since_epoch().count())
        elapsedSeconds = currentTime - m_previousTime;
    m_previousTime = currentTime;

    auto deltaTime = (f32)elapsedSeconds.count();

    m_scale += 0.2f * deltaTime;
    auto currentScale = abs(sin(m_scale));

    OMat4 world, projection, temp;

    temp.setIdentity();
    temp.setScale(OVec3(1, 1, 1));
    world *= temp;

    temp.setIdentity();
    temp.setRotationX(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setRotationY(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setRotationZ(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setTranslation(OVec3(0, 0, 0));
    world *= temp;

    auto displaySize = m_display->getInnerSize();
    projection.setOrthoLH(displaySize.width*0.004f, displaySize.height*0.004f, 0.01f, 100.0f);




    UniformData data = {world, projection};
    m_uniform->setData(&data);

    m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

    m_graphicsEngine->setFaceCulling(BackFace);

    m_graphicsEngine->setWindingOrder(ClockWise);

    m_graphicsEngine->setVertexArrayObject(m_polygonVAO);

    m_graphicsEngine->setUniformBuffer(m_uniform, 0);

    m_graphicsEngine->setShaderProgram(m_shader);

    m_graphicsEngine->bindTexture(m_texture, GL_TEXTURE0);
    ui32 gSamplerLocation;
    glUniform1i(gSamplerLocation, 0);

    //m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);
    m_graphicsEngine->drawIndexedTriangles(TriangleList, 36);


    m_display->present(false);
}
void OGame::onQuit()
{

}
    

void OGame::run()
{   
    onCreate();

    MSG msg = {};
    while (m_isRunning)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        onUpdate();
    }

    onQuit();
}

void OGame::quit()
{
    m_isRunning = false;
}

