bool File_Exists(const char* filePath)
{
	Z_ASSERT(filePath, "No filePath supplied");
	FILE* file = fopen(filePath, "rb");
  
	if(!file)
	{
		return false;
	}
  
	fclose(file);
	return true;
}

i32 File_GetSize(const char* filePath)
{
	Z_ASSERT(filePath, "No filePath supplied");
	i32 fileSize = 0;
	FILE* file = fopen(filePath, "rb");
  
	if(!file)
	{
		Z_ERROR("FAIL Open File: %s", filePath);
		return 0;
	}

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);

	return fileSize;
}

char* File_Read(const char* filePath, i32* fileSize, char* buffer)
{
	Z_ASSERT(filePath, 	"No filePath supplied");
	Z_ASSERT(fileSize, 	"No fileSize supplied");
	Z_ASSERT(buffer, 	"No buffer supplied");

	*fileSize = 0;
  
	FILE* file = fopen(filePath, "rb");
  
	if(!file)
	{
		Z_ERROR("FAIL Open File: %s", filePath);
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	*fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	memset(buffer, 0, *fileSize + 1);
	fread(buffer, sizeof(char), *fileSize, file);
	fclose(file);
	
	return buffer;
}

char* File_Read(const char* filePath, i32* fileSize, Arena* arena)
{
	char* file = nullptr;
	i32 fileSize2 = File_GetSize(filePath);
  
	if(fileSize2)
	{
		char* buffer = ArenaAlloc(arena, fileSize2 + 1);
		file = File_Read(filePath, fileSize, buffer);
	}
  
	return file;
}

void File_Write(const char* filePath, char* buffer, i32 size)
{
	Z_ASSERT(filePath, "No filePath supplied!");
	Z_ASSERT(buffer, "No buffer supplied!");
  
	FILE* file = fopen(filePath, "wb");
  
	if(!file)
	{
		Z_ERROR("FAIL Open File: %s", filePath);
		return;
	}

	fwrite(buffer, sizeof(char), size, file);
	fclose(file);
}

bool File_Copy(const char* fileName, const char* outputName, char* buffer)
{
	i32 fileSize = 0;
	char* data = File_Read(fileName, &fileSize, buffer);

	FILE* outputFile = fopen(outputName, "wb");
  
	if(!outputFile)
	{
		Z_ERROR("FAIL Open File: %s", outputName);
		return false;
	}

	i32 result = fwrite(data, sizeof(char), fileSize, outputFile);
	if(!result)
	{
		Z_ERROR("FAIL Write File: %s", outputName);
		return false;
	}
  
	fclose(outputFile);

	return true;
}

bool File_Copy(const char* fileName, const char* outputName, Arena* arena)
{
	char* file = 0;
	i32 fileSize = File_GetSize(fileName);

	if(fileSize)
	{
		char* buffer = ArenaAlloc(arena, fileSize + 1);
		return File_Copy(fileName, outputName, buffer);
	}

	return false;
}