#include "common.h"
#include "cvars.h"

CVar *CVars = nullptr;

CVar::CVar(const char *name)
{
	_PrevCVar = CVars;
	CVars = this;

	_Name = name;
}

void IntCVar::SetString(std::string value)
{
	std::stringstream s(value);

	if (!(s >> _Value))
		_Value = 0;
}

std::string IntCVar::ToString()
{
	std::stringstream s;
	s << _Value;

	return s.str();
}

void FloatCVar::SetString(std::string value)
{
	std::stringstream s(value);

	if (!(s >> _Value))
		_Value = 0;
}

std::string FloatCVar::ToString()
{
	std::stringstream s;
	s << _Value;

	return s.str();
}

void StringCVar::SetString(std::string value)
{
	_Value = value;
}

std::string StringCVar::ToString()
{
	return _Value;
}