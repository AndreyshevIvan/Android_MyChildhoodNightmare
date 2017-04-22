#include "GameAnim.h"
#include <iostream>

USING_NS_CC;
using namespace std;

CGameAnim* CGameAnim::Create(const string &spriteName, const Rect &frame, size_t framesCount, bool isLoop)
{
	CGameAnim *ret = (new (std::nothrow) CGameAnim);
	if (ret && ret->Init(spriteName, frame, framesCount, isLoop))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);

	return nullptr;
}

bool CGameAnim::Init(const string &spriteName, const Rect &frame, size_t framesCount, bool isLoop)
{
	return true;
}

cocos2d::ActionInterval* CGameAnim::GetAction()
{
	return m_action;
}
