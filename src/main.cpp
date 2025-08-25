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

	i32 user_count = 15;

	Z_INFO("Application started with %d users online.", user_count);

	Z_WARN("Good morning, Crono");
	Z_DEBUG("DEBUG");
    Z_WARN("WARN: TEST");
    Z_INFO("good morning, Crono");
    Z_ERROR("ERROR: Test");
    Z_CRIT("CRIT: Test");

	Uint64 lastTicks = SDL_GetTicks();

	b32 running = true;
    while (running)
	{
        Uint64 now = SDL_GetTicks();
        f32 deltaTime = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        SDL_Event e;
        
        while (SDL_PollEvent(&e)) 
		{
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

		SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
