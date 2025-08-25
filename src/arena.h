struct Arena
{
	size_t capacity;
	size_t used;
	char* memory;
};

Arena CreateArena(size_t size)
{
	Arena arena = {};
	arena.memory = (char*)malloc(size);
  
	if(arena.memory)
	{
    	arena.capacity = size;
		memset(arena.memory, 0, size); // Sets the memory to 0
	}
	else
	{
		Z_ASSERT(false, "FAIL: Alloc Memory");
	}

	return arena;
}

char* ArenaAlloc(Arena* arena, size_t size)
{
	char* result = nullptr;
	size_t allignedSize = (size + 7) & ~ 7; // This makes sure the first 4 bits are 0 
 

	if(arena->used + allignedSize <= arena->capacity)
	{
		result = arena->memory + arena->used;
		arena->used += allignedSize;
	}
	else
	{
		Z_ASSERT(false, "Arena FULL");
	}

	return result;
}