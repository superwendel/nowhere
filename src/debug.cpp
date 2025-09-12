#define CIRCLE_SEGMENTS 64
GLuint circleVAO, circleVBO;

void Debug_InitCircleMesh() 
{
    f32 verts[CIRCLE_SEGMENTS * 2];
    for (int i = 0; i < CIRCLE_SEGMENTS; ++i) 
	{
        f32 angle = (f32)i / CIRCLE_SEGMENTS * 2.0f * M_PI;
        verts[i * 2 + 0] = cosf(angle);
        verts[i * 2 + 1] = sinf(angle);
    }

	glLineWidth(1.0f);

    glGenVertexArrays(1, &circleVAO);
    glGenBuffers(1, &circleVBO);
    glBindVertexArray(circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
    glEnableVertexAttribArray(0);
}

void Debug_DrawCircle(GLuint shader, f32 x, f32 y, f32 radius, f32* proj) 
{
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "uProjection"), 1, GL_FALSE, proj);
    glUniform2f(glGetUniformLocation(shader, "uOffset"), x, y);
    glUniform1f(glGetUniformLocation(shader, "uScale"), radius);
    glUniform4f(glGetUniformLocation(shader, "uColor"), 1.0f, 1.0f, 0.2f, 0.2f); // bright yellow

    glBindVertexArray(circleVAO);
    glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_SEGMENTS);
}