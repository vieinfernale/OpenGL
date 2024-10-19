#version 450 core

// Input from the vertex shader
in vec4 vsColor;
in vec2 vsTex;

out vec4 fsColor;
uniform sampler2D fsTex; // uniform variable of the texture bound 

void main() 
{
    fsColor = texture(fsTex, vsTex);
}