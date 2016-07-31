#ifndef CVARS_H_INCLUDED
#define CVARS_H_INCLUDED

#include "common.h"

class CVar
{
public:
	CVar(const char *name);

	GETTER(std::string, Name)
	GETTER(CVar*, PrevCVar)

	virtual std::string ToString() = 0;

	virtual void SetString(std::string value) = 0;

private:
	const char *_Name;
	CVar *_PrevCVar = nullptr;
};

class IntCVar : public CVar
{
public:
	GETSET(int, Value)

	std::string ToString();
	void SetString(std::string value);

	operator int() const { return _Value; }
	int& operator=(int value) { _Value = value; }

private:
	int _Value;
};

class FloatCVar : public CVar
{
public:
	GETSET(int, Value)

	std::string ToString();
	void SetString(std::string value);

	operator float() const { return _Value; }
	float& operator=(float value) { _Value = value; }

private:
	float _Value;
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

#endif