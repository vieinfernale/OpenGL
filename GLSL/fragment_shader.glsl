#version 450 core

out vec4 fragc;
out vec2 fragt;

in vec4 oc;  // The color from the vertex shader
in vec2 ot;

void main() 
{
    fragc = oc;  // Output the color to the framebuffer
    fragt = ot;
}