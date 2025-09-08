SDL_Window* window;
GameState* gameState;

i32 main()
{
	Init_SDL();
	ZLog_Init(ZLOG_LEVEL_INFO);

	Arena transientStorage = CreateArena(MB(50));
	Arena persistentStorage = CreateArena(MB(256));

	gameState = (GameState*)ArenaAlloc(&persistentStorage, sizeof(GameState));
	if(!gameState)
	{
		Z_ERROR("FAIL: Alloc GameState");
		return -1;
	}

	GLuint shader = Shader_CreateProgram("shaders/sprite.vert", "shaders/sprite.frag");
	u32 bgShader = Shader_CreateProgram("shaders/sprite.vert", "shaders/bg.frag");

	Sprite_Init();
    Camera_Init(1280, 720);

	Background_Init("gfx/bg128.png", 128.0f, 32); // 128px tiles, 32x32 = 4096px area

	Sprite subSprite = Sprite_LoadWithNormal("gfx/SubTest.png", "gfx/SubTest_n.png");

	f32 spriteX = 100.0f; 
	f32 spriteY = 100.0f;
    f32 moveSpeed = 250.0f;

	Z_WARN("Good morning, Crono");
    Z_INFO("good morning, Crono");

	Uint64 lastTicks = SDL_GetTicks();

	b32 running = true;
    while (running)
	{
        Uint64 now = SDL_GetTicks();
        f32 deltaTime = (now - lastTicks) / 1000.0f;
        lastTicks = now;

		SDL_Event e;
        const Uint8* keys = (Uint8*)SDL_GetKeyboardState(NULL);
        
        while (SDL_PollEvent(&e)) 
		{
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

		// Sprite movement
        if (keys[SDL_SCANCODE_W]) spriteY -= moveSpeed * deltaTime;
        if (keys[SDL_SCANCODE_S]) spriteY += moveSpeed * deltaTime;
        if (keys[SDL_SCANCODE_A]) spriteX -= moveSpeed * deltaTime;
        if (keys[SDL_SCANCODE_D]) spriteX += moveSpeed * deltaTime;

		Camera_SetViewport(window);
        Camera_FollowSmooth(spriteX, spriteY, subSprite.width, subSprite.height, 5.0f, deltaTime);
        Camera_UpdateProjection();
        f32* proj = Camera_GetProjection();

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		Background_Draw(bgShader, proj);

		// manually rebind
		glUseProgram(shader);

		vec2 lightDir = { 0.0f, 1.0f }; // light from top

		glUniform2f(glGetUniformLocation(shader, "lightDir"), lightDir.x, lightDir.y);

		Sprite_Draw(shader, subSprite, spriteX, spriteY, proj);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
