typedef struct 
{
    u32 texture;
    u32 normalMap;
    i32 width;
    i32 height;
} Sprite;

u32 spriteVAO = 0;
u32 spriteVBO = 0;
u32 spriteEBO = 0;

u32 Texture_Load(char* path, i32* outW, i32* outH) 
{
    stbi_set_flip_vertically_on_load(0);
    i32 w, h, ch;
    unsigned char* data = stbi_load(path, &w, &h, &ch, 4);
    if (!data) 
	{
        Z_ERROR("Load Texture FAIL: %s\n", path);
        return 0;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);

    if (outW) *outW = w;
    if (outH) *outH = h;
    return tex;
}

void Sprite_Init(void) 
{
	f32 quadVertices[] = 
	{
		// pos   // tex
		0.0f, 0.0f, 0.0f, 0.0f, // top-left
		1.0f, 0.0f, 1.0f, 0.0f, // top-right
		1.0f, 1.0f, 1.0f, 1.0f, // bottom-right
		0.0f, 1.0f, 0.0f, 1.0f  // bottom-left
	};

    u32 quadIndices[] = { 0, 1, 2, 2, 3, 0 };

    glGenVertexArrays(1, &spriteVAO);
    glGenBuffers(1, &spriteVBO);
    glGenBuffers(1, &spriteEBO);

    glBindVertexArray(spriteVAO);

    glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(f32)));
    glEnableVertexAttribArray(1);
}

Sprite Sprite_Load(char* diffusePath) 
{
    Sprite s = {0};
    s.texture = Texture_Load(diffusePath, &s.width, &s.height);
    return s;
}

Sprite Sprite_LoadWithNormal(char* diffusePath, char* normalPath) 
{
    Sprite s = {0};
    s.texture = Texture_Load(diffusePath, &s.width, &s.height);
    s.normalMap = Texture_Load(normalPath, NULL, NULL);
    return s;
}

void Sprite_Draw(GLuint shader, Sprite sprite, f32 x, f32 y, f32* proj) 
{
    glUseProgram(shader);

    glUniformMatrix4fv(glGetUniformLocation(shader, "uProjection"), 1, GL_FALSE, proj);
    glUniform2f(glGetUniformLocation(shader, "uScale"), (f32)sprite.width, (f32)sprite.height);
    glUniform2f(glGetUniformLocation(shader, "uOffset"), x, y);

    // Bind diffuse
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite.texture);
    glUniform1i(glGetUniformLocation(shader, "diffuseMap"), 0);

    // Bind normal
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, sprite.normalMap);
    glUniform1i(glGetUniformLocation(shader, "normalMap"), 1);

    glBindVertexArray(spriteVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}