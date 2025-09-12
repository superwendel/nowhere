#define MAX_LIGHTS 16

typedef struct 
{
    f32 x, y;
    f32 radius;
    f32 intensity;
} PointLight;

PointLight lights[MAX_LIGHTS];
i32 lightCount = 0;

// Camera position (world-space)
extern f32 camX;
extern f32 camY;

void Lighting_Reset(void) 
{
    lightCount = 0;
}

// Add a new point light
// Returns the light index or -1 if full
i32 Lighting_Add(f32 x, f32 y, f32 radius, f32 intensity) 
{
    if (lightCount >= MAX_LIGHTS) return -1;
	lights[lightCount++] = PointLight{ x, y, radius, intensity };
    return lightCount - 1;
}

// Upload lights to the GPU shader
void Lighting_Apply(GLuint shader) 
{
    glUseProgram(shader);
    
    // Send the count
    GLint locCount = glGetUniformLocation(shader, "pointLightCount");
    glUniform1i(locCount, lightCount);

    // Loop through each light and upload its properties
    for (i32 i = 0; i < lightCount; ++i) 
	{
        char name[64];
        
        // Position in world-space (no cam offset here)
        snprintf(name, sizeof(name), "pointLights[%d].position", i);
        GLint locPos = glGetUniformLocation(shader, name);
        glUniform2f(locPos, lights[i].x, lights[i].y);

        // Radius
        snprintf(name, sizeof(name), "pointLights[%d].radius", i);
        GLint locRad = glGetUniformLocation(shader, name);
        glUniform1f(locRad, lights[i].radius);

        // Intensity
        snprintf(name, sizeof(name), "pointLights[%d].intensity", i);
        GLint locInt = glGetUniformLocation(shader, name);
        glUniform1f(locInt, lights[i].intensity);
    }
}