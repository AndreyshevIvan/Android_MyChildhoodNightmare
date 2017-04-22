#pragma once
#include "cocos_custom.h"
#include "cocos2d.h"
#include <string>

class CGameAnim : cocos2d::Object
{
public:
	static CGameAnim* Create(const std::string &spriteName, const cocos2d::Rect &frame, size_t framesCount, bool isLoop = false);
	cocos2d::ActionInterval* GetAction();

private:
	bool Init(const std::string &spriteName, const cocos2d::Rect &frame, size_t framesCount, bool isLoop);
	cocos2d::ActionInterval* m_action;

};