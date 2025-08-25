#define ZLOG_TIMESTAMP 0
#define ZLOG_STRIP_EXTENSION 0

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#if ZLOG_TIMESTAMP
#include <time.h>
#endif

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GRAY    "\x1b[90m"

typedef enum 
{
    ZLOG_LEVEL_DEBUG,
    ZLOG_LEVEL_INFO,
    ZLOG_LEVEL_WARN,
    ZLOG_LEVEL_ERROR,
    ZLOG_LEVEL_CRIT,
    ZLOG_LEVEL_NONE // disable all logging
} LogLevel;

static LogLevel logLevel = ZLOG_LEVEL_INFO;

/**
	* @brief Inits the logger and sets the min level for messages to be displayed
	*
	* @param level The min LogLevel to display
	*/
ZINLINE void ZLog_Init(LogLevel level) 
{
    logLevel = level;
}

/**
	* @brief The core log function. Do not call this directly; use macros instead
	*
	* @param level The level of the message to be logged
	* @param file The source file where the log was triggered (__FILE__)
	* @param line The line number where the log was triggered (__LINE__)
	* @param format The printf-style format string
	* @param ... The variable args for the format string
	*/
static void ZLog_Log(LogLevel level, char* file, i32 line, char* format, ...) 
{
    if (level < logLevel) 
    {
        return; // Don't log below current threshold
    }

    FILE* stream = stdout;
    char* color = ANSI_COLOR_RESET;
    char* levelStr = "UNKN";

    switch (level) 
    {
        case ZLOG_LEVEL_DEBUG:
            levelStr = "DBUG";
            color = ANSI_COLOR_BLUE;
            break;
        case ZLOG_LEVEL_INFO:
            levelStr = "INFO";
            color = ANSI_COLOR_GREEN;
            break;
        case ZLOG_LEVEL_WARN:
            levelStr = "WARN";
            color = ANSI_COLOR_YELLOW;
            stream = stderr;
            break;
        case ZLOG_LEVEL_ERROR:
            levelStr = "EROR";
            color = ANSI_COLOR_RED;
            stream = stderr;
            break;
        case ZLOG_LEVEL_CRIT:
            levelStr = "CRIT";
            color = ANSI_COLOR_RED;
            stream = stderr;
            break;
        case ZLOG_LEVEL_NONE:
			return;
    }

#if ZLOG_TIMESTAMP
    time_t timer;
    char time_buffer[9];
    time(&timer);
    struct tm* tm_info = localtime(&timer);
    strftime(time_buffer, 9, "%H:%M:%S", tm_info);
    fprintf(stream, "%s[%s] ", ANSI_COLOR_GRAY, time_buffer);
#endif

    char* lastSlash = strrchr(file, '/');
    char* lastBackSlash = strrchr(file, '\\');
    char* filenameWithExt = file;
    
    if (lastSlash) 
    {
        filenameWithExt = lastSlash + 1;
    }
    
    if (lastBackSlash && lastBackSlash > lastSlash) 
    {
        filenameWithExt = lastBackSlash + 1;
    }

#if ZLOG_STRIP_EXTENSION // Change fprintf to take fileNameNoExt instead
    char fileNameNoExt[256];
    strncpy(fileNameNoExt, filenameWithExt, sizeof(fileNameNoExt) - 1);
    fileNameNoExt[sizeof(fileNameNoExt) - 1] = '\0';

    char* lastDot = strrchr(fileNameNoExt, '.');
    if (lastDot != NULL) 
    {
        *lastDot = '\0';
    }
#endif

    fprintf(stream, "%s[%-4s]%s %s%s:%d%s: ", color, levelStr, ANSI_COLOR_RESET, ANSI_COLOR_CYAN, filenameWithExt, line, ANSI_COLOR_RESET);

    va_list args;
    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);

    fprintf(stream, "\n");
    fflush(stream);
}

#define Z_DEBUG(...)   ZLog_Log(ZLOG_LEVEL_DEBUG,   __FILE__, __LINE__, __VA_ARGS__)
#define Z_INFO(...)    ZLog_Log(ZLOG_LEVEL_INFO,    __FILE__, __LINE__, __VA_ARGS__)
#define Z_WARN(...)    ZLog_Log(ZLOG_LEVEL_WARN,    __FILE__, __LINE__, __VA_ARGS__)
#define Z_ERROR(...)   ZLog_Log(ZLOG_LEVEL_ERROR,   __FILE__, __LINE__, __VA_ARGS__)
#define Z_CRIT(...)    ZLog_Log(ZLOG_LEVEL_CRIT, __FILE__, __LINE__, __VA_ARGS__)

/**
	* @brief Checks for a condition and terminates app if it is false
	*
	* Use this for checking unrecoverable errors. If the condition is false,
	* it logs a CRIT message with the failed condition and the provided message,
	* then calls abort()
	*
	* ie:
	* int* ptr = malloc(size);
	* ZASSERT(ptr != NULL, "Failed to alloc %zu bytes for player", size);
	*/
#define Z_ASSERT(condition, ...) \
do { \
	if (!(condition)) { \
		ZLog_Log(ZLOG_LEVEL_CRIT, __FILE__, __LINE__, "ASSERT FAIL: (%s) - " __VA_ARGS__, #condition); \
            abort(); \
	} \
} while (0)