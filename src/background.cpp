u32 bgVAO = 0;
u32 bgVBO = 0;
u32 bgEBO = 0;
u32 bgTexture = 0;

ZINLINE void Background_Init(char* texturePath, f32 tileSize, f32 tileCount) 
{
    f32 size = tileSize * tileCount;

    f32 bgVerts[] = 
	{
        // pos       // tex (tile units)
        0.0f,    0.0f,      0.0f,        0.0f,
        size,    0.0f,   tileCount,      0.0f,
        size,  size,     tileCount,  tileCount,
        0.0f,  size,         0.0f,   tileCount
    };
    u32 bgIndices[] = { 0, 1, 2, 2, 3, 0 };

    glGenVertexArrays(1, &bgVAO);
    glBindVertexArray(bgVAO);

    glGenBuffers(1, &bgVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVerts), bgVerts, GL_STATIC_DRAW);

    glGenBuffers(1, &bgEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgIndices), bgIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    bgTexture = Texture_Load(texturePath, 0, 0);
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

ZINLINE void Background_Draw(u32 shader, f32* projection) 
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "uProjection"), 1, GL_FALSE, projection);
	glUniform2f(glGetUniformLocation(shader, "uScale"), 1.0f, 1.0f);
	glUniform2f(glGetUniformLocation(shader, "uOffset"), 0.0f, 0.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bgTexture);
	glUniform1i(glGetUniformLocation(shader, "diffuseMap"), 0);

	glBindVertexArray(bgVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}