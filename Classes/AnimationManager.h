#pragma once
#include "cocos_custom.h"
#include "cocos2d.h"
#include <string>

namespace
{
	const float FRAME_DELAY = 0.1f;
}

class CAnimManager : cocos2d::Object
{
public:
	static cocos2d::RefPtr<cocos2d::Animation> CreateAnim(
		const std::string &spriteName,
		const cocos2d::Size &frameSize,
		size_t framesCount,
		float frameDelay = FRAME_DELAY
	);

};