#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "common.h"

class Frame
{
public:
	Frame(std::string texture, float duration);
	
	GLuint Sprite;
	float Time;
};

class Animation
{
public:
	Animation() {}
	Animation(std::initializer_list<Frame> anim);

	std::vector<Frame> Frames;
};

#endif // ANIMATION_H_INCLUDED