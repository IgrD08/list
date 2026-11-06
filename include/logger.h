#ifndef LOGGER_H
#define LOGGER_H

#define LOG(LOG_MESSAGE, ...) logWrite(__FILE__, __LINE__, __func__, LOG_MESSAGE, ##__VA_ARGS__)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

extern FILE *logFile;

void logWrite(const char *file, int line, const char *funcconst, const char *message, ...);

#endif
