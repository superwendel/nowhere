#version 330 core

in vec2 TexCoord;
in vec2 FragWorldPos;      // ← from sprite.vert

out vec4 FragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

// ——— Directional Light ———
uniform vec2  dirLightDir;
uniform float ambientStrength;

// ——— Point Lights ———
#define MAX_LIGHTS 16
struct PointLight 
{
    vec2  position;   // world-space
    float radius;
    float intensity;
};

uniform int        pointLightCount;
uniform PointLight pointLights[MAX_LIGHTS];

// ——— Spotlight ———
uniform vec2  spotPos;       // world-space
uniform vec2  spotDir;
uniform float spotCutoff;    // cos(angle)
uniform float spotIntensity;

void main() 
{
    // fetch textures
    vec4 baseColor = texture(diffuseMap, TexCoord);
    vec3 normal    = normalize(texture(normalMap, TexCoord).rgb * 2.0 - 1.0);

    // this is your sprite’s pixel-position in world space
    vec2 fragXY = FragWorldPos;

    // — Directional Lighting —
    vec3  Ld  = normalize(vec3(dirLightDir, 1.0));
    float diff = max(dot(normal, Ld), 0.0);
    float dirLighting = ambientStrength + diff;

    // — Point Lights —
    float pointTotal = 0.0;
    for (int i = 0; i < pointLightCount; ++i) 
	{
        vec2  toLight = pointLights[i].position - fragXY;
        float d       = length(toLight);
        float atten   = clamp(1.0 - d / pointLights[i].radius, 0.0, 1.0);
        float pdiff   = max(dot(normal, normalize(vec3(toLight, 1.0))), 0.0);
        pointTotal   += pdiff * atten * pointLights[i].intensity;
    }

    // — Spotlight —
    vec2  toFrag      = normalize(fragXY - spotPos);
    float angleCos    = dot(normalize(spotDir), toFrag);
    float spotMask    = smoothstep(spotCutoff, spotCutoff + 0.05, angleCos);
    float spotDiffuse = max(dot(normal, vec3(-toFrag, 1.0)), 0.0);
    float spotLight   = spotDiffuse * spotMask * spotIntensity;

    // combine
    float totalLight = clamp(dirLighting + pointTotal + spotLight, 0.0, 1.0);
    vec3  litColor   = baseColor.rgb * totalLight;

    FragColor = vec4(litColor, baseColor.a);
}