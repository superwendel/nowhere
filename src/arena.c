typedef struct 
{
	size_t capacity;
	size_t used;
	char* memory;
} Arena;

Arena CreateArena(size_t size)
{
	Arena arena = {0};
	arena.memory = (char*)malloc(size);
  
	if(arena.memory)
	{
    	arena.capacity = size;
		memset(arena.memory, 0, size);
	}
	else
	{
		SDL_assert("FAIL: Alloc Memory");
	}

	return arena;
}

char* ArenaAlloc(Arena* arena, size_t size)
{
	char* result = NULL;
	size_t allignedSize = (size + 7) & ~ 7; // This makes sure the first 4 bits are 0 
 
	if(arena->used + allignedSize <= arena->capacity)
	{
		result = arena->memory + arena->used;
		arena->used += allignedSize;
	}
	else
	{
		SDL_assert("ARENA FULL");
	}

	return result;
}