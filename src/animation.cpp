#include "common.h"
#include "animation.h"
#include "textures.h"

Frame::Frame(std::string texture, float duration)
{
	Sprite = GetTexture(texture);
	Time = duration;
};

Animation::Animation(std::initializer_list<Frame> anim)
{
	for (const Frame &frame : anim)
		Frames.push_back(frame);
}
