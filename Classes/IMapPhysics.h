#pragma once

#include "cocos_custom.h"

class IMapPhysics
{
public:
	virtual bool CanStandOn(const cocos2d::Rect &body) = 0;

};