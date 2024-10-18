#version 450 core

layout(location = 0) in vec3 Position;    
layout(location = 1) in vec4 Color;        
layout(location = 2) in vec2 Tex;        

// Output to the fragment shader
out vec4 outColor;                    
out vec2 outTex;

void main() {

    gl_Position = vec4(Position, 1.0);
    outColor = Color;
    outTex = Tex;

}