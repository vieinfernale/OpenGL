#version 450 core

layout(location = 0) in vec3 vp;        // Position attribute
layout(location = 1) in vec4 vc;        // Color attribute
layout(location = 2) in vec2 vt;        // Texture coordinate attribute


out vec4 oc;                        // Output color to the fragment shader
out vec2 ot;

void main() {

    gl_Position = vec4(vp, 1.0);
    oc = vc;
    ot = vt;
    // outcolor = vec4(0.5, 0.0, 0.0, 1.0);

}