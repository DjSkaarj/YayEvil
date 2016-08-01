#include "common.h"
#include "cvars.h"
#include "math.h"
#include "log.h"

CVar *CVars = nullptr;

std::map<std::string, CVar*> CVarsByName;

void YE_InitCVars()
{
	for (CVar *cvar = CVars; cvar != nullptr; cvar = cvar->PrevCVar())
		CVarsByName[cvar->Name()] = cvar;
}

void YE_ReadConfig()
{
	Log(0, "[Config] Loading configuration file...");

	std::ifstream rc;
	rc.open("config.cfg", std::ios::in);
	if (!rc.is_open())
	{
		Log(0, "[Config] Configuration file wasn't found, the new one will be created on exit.");
		return;
	}

	while (!rc.eof())
		YE_ReadConfigLine(&rc);

	Log(0, "[Config] Configuration file was loaded.");
	rc.close();
}

void YE_ReadConfigLine(std::ifstream *c)
{
	std::string cvar, value;
	*c >> cvar;

	if (!cvar.size() || c->eof())
		return;
	
	*c >> value;

	if (!value.size() || c->eof())
	{
		Log(0, "[Config] [Warning] CVar %s: expected value.", cvar.c_str());
		return;
	}

	if (!CheckCVar(cvar))
		return;
	
	GetCVar(cvar)->SetString(value);
}

void YE_WriteConfig()
{
	Log(0, "[Config] Writting configuration file...");

	std::ofstream wc;
	wc.open("config.cfg", std::ios::out | std::ios::trunc);

	for (auto &i : CVarsByName)
		wc << i.first << " " << i.second->ToString() << std::endl;

	Log(0, "[Config] Configuration file was created...");
}

bool CheckCVar(std::string name)
{
	if (CVarsByName.find(name) == CVarsByName.end())
	{
		Log(0, "[Config] [Warning] Unknown CVar %s!", name.c_str());
		CVarsByName.erase(CVarsByName.end());
		return false;
	}
	return true;
}

CVar* GetCVar(std::string name)
{
	if (!CheckCVar(name))
		return nullptr;

	return CVarsByName[name];
}

CVar::CVar(std::string name)
{
	_PrevCVar = CVars;
	CVars = this;

	_Name = name;
	std::transform(_Name.begin(), _Name.end(), _Name.begin(), ::tolower);
}

IntCVar::IntCVar(std::string name, int value, int lrange, int rrange) : CVar(name) 
{
	_Value = clip(value, lrange, rrange);
}

FloatCVar::FloatCVar(std::string name, float value, float lrange, float rrange) : CVar(name)
{
	_Value = clip(value, lrange, rrange);
}

void IntCVar::SetString(std::string value)
{
	std::stringstream s(value);

	if (!(s >> _Value))
		_Value = 0;

	clip(_Value, LRange, RRange);
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

	clip(_Value, LRange, RRange);
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
	std::transform(_Value.begin(), _Value.end(), _Value.begin(), ::tolower);
}

std::string StringCVar::ToString()
{
	return _Value;
}

// window

INT_CVAR(w_width, SCREEN_WIDTH_DEF, SCREEN_WIDTH_MIN, SCREEN_WIDTH_MAX)
INT_CVAR(w_height, SCREEN_HEIGHT_DEF, SCREEN_HEIGHT_MIN, SCREEN_HEIGHT_MAX)
FLAG_CVAR(w_fullscreen, 0)

// render

FLAG_CVAR(r_multisample, 0)
FLAG_CVAR(r_shadows, 1)
INT_CVAR(r_shadowquality, 10.0f, 1.0f, 15.0f)
FLOAT_CVAR(r_shadowintensity, 0.6f, 0.1f, 1.0f)
FLOAT_CVAR(r_shadowscale, 1.0f, 1.0f, 3.0f)

// log

FLAG_CVAR(l_textures, 0)
FLAG_CVAR(l_map, 0)