#include "common.h"
#include "animation.h"
#include "textures.h"
#include "log.h"

Frame::Frame(std::string texture, float duration)
{
	Sprite = texture;
	Time = duration;
};

Animation::Animation(std::initializer_list<Frame> anim)
{
	for (const Frame &frame : anim)
		Frames.push_back(frame);
}

void Animation::SwitchFrame()
{
	if (Index == Frames.size() - 1)
		Index = 0;
	else
		Index++;

	Timer = 0;
}

void Animation::Update()
{
	if (Timer > Frames[Index].Time)
		SwitchFrame();
	
	Timer += deltatime;
}

std::string Animation::GetSprite()
{
	return Frames[Index].Sprite;
}

Animation AnimBarrel = { { "barrel1", 0.3f },{ "barrel2", 0.3f } };