#version 450 core

out vec4 fragColor;
out vec2 fragTex;

// Input from the vertex shader
in vec4 outColor;
in vec2 outTex;

void main() 
{
    fragColor = outColor;
    fragTex = outTex;
}