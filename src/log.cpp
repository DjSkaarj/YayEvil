#include "common.h"
#include "log.h"

//By RevenantX

FILE *logfile;
FILE *logfile_err;

// Initializes the very simple logging system.
void Log_Init()
{
	logfile = fopen("log.txt", "w");
    logfile_err = fopen("log_err.txt", "w");
	if (logfile == NULL || logfile_err == NULL)
	{
		printf("[Error] Failed to open log files for writing!\n");
		return;
	}
}

// Writes a message to the log.
// Uses printf formatting.
// Newline is automatically added to the end.
void Log(bool iferror, const char *format, ...)
{
	Uint32 time = SDL_GetTicks();

	Uint32 hours   = time / 1000 / 3600;
	Uint32 minutes = time / 1000 % 3600 / 60;
	Uint32 seconds = time / 1000 % 60;
	Uint32 milliseconds = time % 1000;

	va_list args;
	va_start(args, format);

	if (logfile != NULL)
	{
	    if(iferror)
        {
            fprintf (logfile, "[%.2u:%.2u:%.2u:%.3u] [Error] Critical error took place! Look log_err.txt for more info.\n", hours, minutes, seconds, milliseconds);
            fprintf (logfile_err, "[%.2u:%.2u:%.2u:%.3u] ", hours, minutes, seconds, milliseconds);
            vfprintf(logfile_err, format, args);
            fprintf (logfile_err, "\n");
            fflush  (logfile_err);
        }
		fprintf (logfile, "[%.2u:%.2u:%.2u:%.3u] ", hours, minutes, seconds, milliseconds);
		vfprintf(logfile, format, args);
		fprintf (logfile, "\n");
		fflush  (logfile);
		return;
	}

    if(iferror)
    {
            fprintf (stdout, "[%.2u:%.2u:%.2u:%.3u] [Error] Critical error took place! Look stderr for more info.\n", hours, minutes, seconds, milliseconds);
            fprintf (stderr, "[%.2u:%.2u:%.2u:%.3u] [Error] ", hours, minutes, seconds, milliseconds);
            vfprintf(stderr, format, args);
            fprintf (stderr, "\n");
            fflush  (stderr);
    }

	fprintf (stdout, "[%.2u:%.2u:%.2u:%.3u] ", hours, minutes, seconds, milliseconds);
	vfprintf(stdout, format, args);
	fprintf (stdout, "\n");
	fflush  (stdout);
}
