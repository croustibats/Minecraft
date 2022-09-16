#version 410 core

layout (row_major) uniform UniformData
{
    mat4 world;
    mat4 projection;
};


layout(location=0) in vec3 position;
layout(location=1) in vec2 texcoord;

out vec2 texcoord0;

void main()
{
    vec4 pos = vec4(position, 1) * world;
    pos = pos * projection;
    gl_Position = pos;
    
    texcoord0 = texcoord;
}