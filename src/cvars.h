#ifndef CVARS_H_INCLUDED
#define CVARS_H_INCLUDED

#include "common.h"

#define INT_CVAR(Name, Value, LeftRange, RightRange) IntCVar Name(# Name, Value, LeftRange, RightRange);
#define FLAG_CVAR(Name, Value) IntCVar Name(# Name, Value, 0, 1);
#define FLOAT_CVAR(Name, Value, LeftRange, RightRange) FloatCVar Name(# Name, Value, LeftRange, RightRange);
#define STRING_CVAR(Name, Value, LeftRange, RightRange) IntCVar Name(# Name, Value);

class CVar
{
public:
	CVar(std::string name);

	GETTER(std::string, Name)
	GETTER(CVar*, PrevCVar)

	virtual std::string ToString() = 0;

	virtual void SetString(std::string value) = 0;

private:
	std::string _Name;
	CVar *_PrevCVar = nullptr;
};

class IntCVar : public CVar
{
public:
	IntCVar(std::string name, int value, int lrange, int rrange);

	GETSET(int, Value)

	std::string ToString();
	void SetString(std::string value);

	operator int() const { return _Value; }
	int& operator=(int value) { _Value = value; }

private:
	int _Value;
	int LRange = INT_MIN;
	int RRange = INT_MAX;
};

class FloatCVar : public CVar
{
public:
	FloatCVar(std::string name, float value, float lrange, float rrange);

	GETSET(float, Value)

	std::string ToString();
	void SetString(std::string value);

	operator float() const { return _Value; }
	float& operator=(float value) { _Value = value; }

private:
	float _Value;
	float LRange = FLT_MIN;
	float RRange = FLT_MAX;
};

class StringCVar : public CVar
{
public:
	GETSET(std::string, Value)

	std::string ToString();
	void SetString(std::string value);

	operator std::string() const { return _Value; }
	std::string& operator=(std::string value) { _Value = value; }

private:
	std::string _Value;
};

void YE_InitCVars();
bool CheckCVar(std::string name);
CVar* GetCVar(std::string name);
void YE_ReadConfig();
void YE_ReadConfigLine(std::ifstream *c);
void YE_WriteConfig();

#endif