#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

void Log_Init();

void Log(bool iferror, const char *format, ...);

#endif // LOG_H_INCLUDED
