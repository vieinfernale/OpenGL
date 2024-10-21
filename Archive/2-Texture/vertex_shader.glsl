#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;        
layout(location = 2) in vec2 Tex; 

layout(location = 1) out vec4 vsColor;
layout(location = 2) out vec2 vsTex;

void main() {
    gl_Position = vec4(Position, 1.0);
    vsColor = Color;
    vsTex = Tex;
}