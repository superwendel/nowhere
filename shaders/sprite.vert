#version 330 core
layout (location = 0) in vec2 aPos;   // sprite-local (0…w, 0…h)
layout (location = 1) in vec2 aTex;

uniform mat4 uProjection;             // orthographic over [camX .. camX+320] × [camY .. camY+180]
uniform vec2 uScale;                  // e.g. (64,64) to draw a 64×64 sprite
uniform vec2 uOffset;                 // world position of the sprite

out vec2 TexCoord;
out vec2 FragWorldPos;                // <— pass this to the fragment

void main() 
{
    // build sprite-corners in world-pixel coords
    vec2 worldPos = aPos * uScale + uOffset;
    FragWorldPos = worldPos;

    // project to NDC
    gl_Position = uProjection * vec4(worldPos, 0.0, 1.0);

    TexCoord = aTex;
}