#include "AnimationManager.h"
#include <iostream>

USING_NS_CC;
using namespace std;

AnimationPtr CAnimManager::CreateAnim(
	const string &spriteName,
	const Size &frameSize,
	size_t framesCount,
	float frameDelay)
{
	AnimationPtr animation(new (std::nothrow) Animation);
	if (!animation)
	{
		CC_SAFE_RELEASE(animation);
		return nullptr;
	}

	Vector<SpriteFrame*> animationFrames(framesCount);
	auto sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
	auto texture = sprite->getTexture();
	auto spriteRect = sprite->getRect();
	Rect frameRect(spriteRect.origin, frameSize);

	for (size_t i = 0; i < framesCount; i++)
	{
		auto frame = SpriteFrame::createWithTexture(texture, frameRect);
		animationFrames.pushBack(frame);
		frameRect.origin.x += frameSize.width;
	}

	animation->initWithSpriteFrames(animationFrames, frameDelay);
	animation->autorelease();
	return animation;
}