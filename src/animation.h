#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "common.h"

extern float deltatime;

class Frame
{
public:
	Frame(std::string texture, float duration);
	
	std::string Sprite;
	float Time;
};

class Animation
{
public:
	Animation() {}
	Animation(std::initializer_list<Frame> anim);

	void SwitchFrame();
	void Update();
	std::string GetSprite();

	float Timer;
	int Index;
	std::vector<Frame> Frames;
};

extern Animation AnimBarrel;

#endif // ANIMATION_H_INCLUDED