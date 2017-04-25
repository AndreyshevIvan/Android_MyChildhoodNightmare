#include "AnimationManager.h"
#include <iostream>

USING_NS_CC;
using namespace std;

cocos2d::RefPtr<Animation> CAnimManager::CreateAnim(
	const string &spriteName,
	const Size &frameSize,
	size_t framesCount,
	float frameDelay)
{
	cocos2d::RefPtr<Animation> animation(new (std::nothrow) Animation);
	if (!animation)
	{
		CC_SAFE_RELEASE(animation);
		return nullptr;
	}

	Vector<SpriteFrame*> animationFrames(framesCount);
	auto cache = SpriteFrameCache::getInstance();
	auto texture = cache->getSpriteFrameByName(spriteName)->getTexture();
	auto spriteRect = cache->getSpriteFrameByName(spriteName)->getRect();
	Rect frameRect(spriteRect.origin.x, spriteRect.origin.y, frameSize.width, frameSize.height);

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