#include "../include/logger.h"

FILE *logFile = NULL;

void logWrite(const char *file, int line, const char *func, const char *message, ...)
{
    time_t timeInSeconds = time(NULL);

    tm *parsedTime = localtime(&timeInSeconds);

    char time[32] = {};
    strftime(time, 32, "%Y-%m-%d %H:%M:%S", parsedTime);

    fprintf(logFile, "[%s] [LOG] [%s:%d] [%s] ", time, file, line, func);

    va_list args;

    va_start(args, message);

    vfprintf(logFile, message, args);

    va_end(args);

    putc('\n', logFile);

    return;
}
