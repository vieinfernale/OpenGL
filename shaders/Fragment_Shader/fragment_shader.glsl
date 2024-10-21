#version 460 core

layout(location = 0) in vec3 Position;  // Input from vertex shader
layout(location = 1) in vec4 Color;     
layout(location = 2) in vec2 Tex;       

layout(location = 0) out vec4 fsTextureColor;  // Output to the framebuffer

layout(binding = 0) uniform sampler2D fsTex;   // Uniform (Global Shader Variable) Texture (type sampler) 

void main() 
{
    fsTextureColor = texture(fsTex, Tex);      // Color (drawing) retrieved : bound texture (fsTex), coordinates (Tex)
}