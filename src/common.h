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
#define SCALE_STEP 8.0

#define COLLISION_OFFSET 0.06

#define SCREEN_WIDTH_MIN 320
#define SCREEN_HEIGHT_MIN 240
#define SCREEN_WIDTH_DEF 800
#define SCREEN_HEIGHT_DEF 600

#define AO_SIZE 0.25
#define AO_COLOR 0.2f

#define GETTER(Type, X) Type X() const { return _##X; }
#define SETTER(Type, X) void Set##X(const Type &value) { _##X = value; }
#define GETSET(Type, X) GETTER(Type, X) SETTER(Type, X)

#define FGETTER(Name, X, FLAGS) bool Name() const { return _##FLAGS & X; }
#define FSETTER(Name, X, FLAGS) void Set##Name(bool set) { if (set) _##FLAGS |= X; else _##FLAGS &= ~X; }
#define FGETSET(Name, X, FLAGS) FGETTER(Name, X, FLAGS) FSETTER(Name, X, FLAGS)

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
