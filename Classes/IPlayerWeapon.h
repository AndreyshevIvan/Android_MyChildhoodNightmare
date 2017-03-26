#pragma once

#include "cocos_custom.h"
#include "Bullet.h"

class IPlayerWeapon
{
public:
	virtual std::vector<cocos2d::RefPtr<CBullet>> Fire(Direction direction) = 0;
	virtual bool IsReady() = 0;

};