#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 uProjection;
uniform vec2 uOffset;
uniform float uScale;

void main() 
{
    vec2 pos = aPos * uScale + uOffset;
    gl_Position = uProjection * vec4(pos, 0.0, 1.0);
}