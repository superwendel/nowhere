char* load_file(char* path) 
{
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char* data = (char*)malloc(size + 1);
    fread(data, 1, size, f);
    data[size] = 0;
    fclose(f);
    return data;
}

u32 Shader_Compile(char* path, GLenum type) 
{
    char* src = load_file(path);
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, (char**)&src, NULL);
    glCompileShader(shader);
    free(src);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        Z_ERROR("Shader Error (%s): %s\n", path, log);
    }
    return shader;
}

u32 Shader_CreateProgram(char* vs_path, char* fs_path) 
{
    u32 vs = Shader_Compile(vs_path, GL_VERTEX_SHADER);
    u32 fs = Shader_Compile(fs_path, GL_FRAGMENT_SHADER);
    u32 program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}