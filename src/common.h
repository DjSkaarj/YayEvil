#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#define GL_MULTISAMPLE 0x809D

#include "glew.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include "SDL_image.h"

#include <cstdio>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "actors.h"
#include "tiles.h"
#include "map.h"
#include "renderer.h"
#include "strings.h"
#include "tinydir.h"
#include "log.h"
#include "geometry.h"

using std::min;
using std::max;

#endif // COMMON_H_INCLUDED
