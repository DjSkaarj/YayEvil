#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include "glew.h"
#include <GL/gl.h>

#include <SDL2/SDL.h>
#include "SDL_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdio>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <string>
#include <sstream>

#include "tinydir.h"

#define SCALE_MIN 8.0
#define SCALE_MAX 256.0
#define UNUSED(expr) do { (void)(expr); } while (0)

typedef unsigned char byte;

using std::min;
using std::max;
using std::move;
using std::unique_ptr;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif // COMMON_H_INCLUDED
