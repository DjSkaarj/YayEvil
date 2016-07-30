#include "common.h"

#include "log.h"

FILE* file;

bool YE_EndsWith(const char *str, const char *ending)
{
    int len1 = strlen(str);
    int len2 = strlen(ending);

    if (len1 < len2)
        return false;

    return !memcmp(&str[len1 - len2], ending, len2);
}

void YE_StrToLower(char *str)
{
    while (*str != 0)
    {
        *str = tolower(*str);
        str++;
    }
}

void YE_InitParser(FILE *rfile)
{
    file=rfile;
}

bool YE_NextLine()
{
    for ( ; ; )
    {
        int c = fgetc(file);
        if (c == '\n')
            return true;
        if (c == EOF)
            return false;
    }
}

char* YE_ReadString()
{
    char *str = new char[255];
    if (!fscanf(file, " %255s", str))
    {
        Log(1, "[YE_ReadString()] Expected a string");
        exit(1);
    }
    return str;
}

void YE_ReadStringA(char *buf, int maxsize)
{
    char format[32];

    snprintf(format, sizeof(format), " %%%ds", (int)(maxsize-1));
    if (!fscanf(file, format, buf))
    {
        Log(1, "[YE_ReadStringA()] Expected a string");
        exit(1);
    }
}

int YE_ReadInt()
{
    int i;
    if (!fscanf(file, " %d", &i))
    {
        Log(1, "[YE_ReadInt()] Expected an integer");
        exit(1);
    }
    return i;
}

float YE_ReadFloat()
{
    float i;
    if (!fscanf(file, " %f", &i))
    {
        Log(1, "[YE_ReadFloat()] Expected a float");
        exit(1);
    }
    return i;
}

std::string NumberToString(float number) 
{
	std::ostringstream buff;
	buff << number;
	return buff.str();
}
