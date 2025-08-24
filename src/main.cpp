SDL_Window* window;

i32 main()
{
	Init_SDL();
	ZLog_Init(ZLOG_LEVEL_INFO);

	i32 user_count = 15;

	ZLOG_INFO("Application started with %d users online.", user_count);

	ZLOG_WARN("Good morning, Crono");
	ZLOG_DEBUG("DEBUG");
    ZLOG_WARN("WARN: TEST");
    ZLOG_INFO("good morning, Crono");
    ZLOG_ERROR("ERROR: Test");
    ZLOG_CRIT("CRIT: Test");

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
