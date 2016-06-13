#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

extern bool YE_Cmd;

void Log_Init();

void Log(bool iferror, const char *format, ...);

#endif // LOG_H_INCLUDED
