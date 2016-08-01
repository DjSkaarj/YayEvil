#include "common.h"
#include "map.h"

#include "log.h"
#include "math.h"
#include "strings.h"
#include "states.h"
#include "cvars.h"

YE_Map::YE_Map()
{
    Rcolor = 1.0;
    Gcolor = 1.0;
    Bcolor = 1.0;

    BGRcolor = 0.0;
    BGGcolor = 0.0;
    BGBcolor = 0.0;

    ARcolor = 0.5;
    AGcolor = 0.5;
    ABcolor = 0.5;

    PlayerX = 0;
    PlayerY = 0;
}

int YE_Map::Index2d(Vector2i pos) const
{
    return pos.x + (pos.y * Size.x);
}

void YE_Map::TileDraw(Vector2i pos) const
{
    Tiles[Index2d(pos)].Draw(pos);
}

bool YE_Map::TileInMap(Vector2i pos) const
{
    return Rect().contains(pos);
}

bool YE_Map::TileExists(Vector2i pos) const
{
    if (!TileInMap(pos) || (!TileTexture(pos))) return false;

    return true;
}

bool YE_Map::TileIsSolid(Vector2i pos) const
{
    if (!TileExists(pos)) return true;

    return Tiles[Index2d(pos)].Solid;
}

GLuint YE_Map::TileTexture(Vector2i pos) const
{
    if (!TileInMap(pos)) return false;

    return Tiles[Index2d(pos)].Texture;
}

void YE_Map::SetTileSolid(Vector2i pos, bool x)
{
    if (!TileInMap(pos)) return;

    Tiles[Index2d(pos)].Solid = x;
}

void YE_Map::SetTileTexture(Vector2i pos, GLuint x)
{
    if (!TileInMap(pos)) return;

    Tiles[Index2d(pos)].Texture = x;
}

void YE_LoadMap (const char *filename)
{
    FILE* level;

    Log(0, "[Map loader] Opening '%s'...", filename);
    level = fopen(filename, "r");
    if(!level)
        Log(1, "[Map loader] Couldn't open map file: '%s'!", filename);

    int width, height;

    YE_InitParser(level);
    YE_ReadString();
    width = YE_ReadInt();
    height = YE_ReadInt();

    stmap.Size = Vector2i(width, height);
    Log(0, "[Map loader] Parsing map '%s' [%d,%d]...", filename, width, height);

    stmap.Tiles = new Tile[width*height];

	while (YE_NextLine()) YE_ParseLine();

    fclose(level);
    Log(0, "[Map loader] Finished parsing '%s'!", filename);
}

void YE_ParseLine()
{
	char cmd[255];
	YE_ReadStringA(cmd, 255);

	if (!strcmp(cmd, "tile"))
	{
		int x = YE_ReadInt();
		int y = YE_ReadInt();

		Vector2i vec = Vector2i(x, y);

		if (!stmap.TileInMap(vec))
			Log(0, "[Map loader] Tile at [%d,%d] is outside of map[%d,%d]!", x, y, stmap.Size.x, stmap.Size.y);
		else
		{
			char texture[255];
			YE_ReadStringA(texture, 255);
			YE_StrToLower(texture);
			std::string s = texture;
			s.erase(s.end() - 4, s.end());

			int solid = YE_ReadInt();

			stmap.SetTileSolid(vec, solid);
			stmap.SetTileTexture(vec, Textures[s]);

			if (l_map)
				Log(0, "[Map loader] Registered new tile [%d,%d]: texture=%s solid=%d", x, y, texture, solid);
		}
	}

	else if (!strcmp(cmd, "actor"))
	{
		float x = YE_ReadFloat();
		float y = YE_ReadFloat();
		char name[255];
		YE_ReadStringA(name, 255);
		std::string s = name;
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);

		Actor actorbuff(Vector2f(x, y));
		if (ActorTypes.find(s) == ActorTypes.end())
		{
			Log(0, "[Map loader] [Warning] Actor name '%s' isn't presented in YE! Skipping actor...", name);
			ActorTypes.erase(ActorTypes.end());
			return;
		}

		actorbuff.CurrentState = ActorTypes[name]->Clone();
		actorbuff.CurrentState->Enter(&actorbuff);

		actorbuff.SetName(name);
		stmap.Actors.push_back(actorbuff);

		if (l_map)
			Log(0, "[Map loader] Parsed actor %s (%f; %f)", name, x, y);
	}

	else if (!strcmp(cmd, "light"))
	{
		Light lightbuff;
		lightbuff.pos.x = YE_ReadFloat();
		lightbuff.pos.y = YE_ReadFloat();

		lightbuff.Radius = YE_ReadFloat();
		lightbuff.RColor = YE_ReadFloat();
		lightbuff.GColor = YE_ReadFloat();
		lightbuff.BColor = YE_ReadFloat();
		stmap.Lights.push_back(lightbuff);
		if (l_map)
			Log(0, "[Map loader] Registered new light [%f,%f]: radius=%f color=%f|%f|%f", lightbuff.pos.x, lightbuff.pos.y, lightbuff.Radius, lightbuff.RColor, lightbuff.GColor, lightbuff.BColor);
	}

	else if (!strcmp(cmd, "globalcolor"))
	{
		stmap.Rcolor = std::min(1.0f, YE_ReadFloat());
		stmap.Gcolor = std::min(1.0f, YE_ReadFloat());
		stmap.Bcolor = std::min(1.0f, YE_ReadFloat());
		if (l_map)
			Log(0, "[Map loader] Set global color to: %f %f %f", stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
	}

	else if (!strcmp(cmd, "backgroundcolor"))
	{
		stmap.BGRcolor = std::min(1.0f, YE_ReadFloat());
		stmap.BGGcolor = std::min(1.0f, YE_ReadFloat());
		stmap.BGBcolor = std::min(1.0f, YE_ReadFloat());
		if (l_map)
			Log(0, "[Map loader] Set background color to: %f %f %f", stmap.BGRcolor, stmap.BGGcolor, stmap.BGBcolor);
	}

	else if (!strcmp(cmd, "ambientcolor"))
	{
		stmap.ARcolor = std::min(1.0f, YE_ReadFloat());
		stmap.AGcolor = std::min(1.0f, YE_ReadFloat());
		stmap.ABcolor = std::min(1.0f, YE_ReadFloat());
		if (l_map)
			Log(0, "[Map loader] Set ambient color to: %f %f %f", stmap.ARcolor, stmap.AGcolor, stmap.ABcolor);
	}

	else if (!strcmp(cmd, "playerstart"))
	{
		stmap.PlayerX = clip(YE_ReadFloat(), 0.0f, (float)stmap.Size.x);
		stmap.PlayerY = clip(YE_ReadFloat(), 0.0f, (float)stmap.Size.y);
		if (l_map)
			Log(0, "[Map loader] Player spawn: %f %f", stmap.PlayerX, stmap.PlayerY);
	}

	else if (!strcmp(cmd, "#"))
	{}

	else Log(0, "[Map loader] [Warning] '%s' is invalid map command! Skipping command...", cmd);
}