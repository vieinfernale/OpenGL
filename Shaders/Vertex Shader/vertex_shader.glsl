#version 450 core

layout(location = 0) in vec3 Position;    
layout(location = 1) in vec4 Color;        
layout(location = 2) in vec2 Tex;        

// Output to the fragment shader
out vec4 vsColor;                    
out vec2 vsTex;

void main() {

    gl_Position = vec4(Position, 1.0);
    vsColor = Color;
    vsTex = Tex;

}