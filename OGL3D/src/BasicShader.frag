#version 410 core

layout(location = 0) out vec4 FragColor;

in vec2 texcoord0;

uniform sampler2D gSampler;

void main()
{
    FragColor = texture(gSampler, texcoord0);
}