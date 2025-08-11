SDL_Window* window;

int main() 
{
	Init_SDL();

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

		//Update
		//Render
		
		SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}