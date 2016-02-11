#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

bool YE_EndsWith(const char *str, const char *ending);
void YE_StrToLower(char *str);
void YE_InitParser(FILE* rfile);
bool YE_NextLine();
char* YE_ReadString();
void YE_ReadStringA(char* buf, int maxsize);
int YE_ReadInt();
float YE_ReadFloat();

#endif // STRINGS_H_INCLUDED
