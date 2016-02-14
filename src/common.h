#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#include "glew.h"
#include <GL/gl.h>

#include <SDL/SDL.h>
#include "SDL_image.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <cstdio>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "tinydir.h"

#define UNUSED(expr) do { (void)(expr); } while (0)

using std::min;
using std::max;
using std::unique_ptr;

#endif // COMMON_H_INCLUDED
