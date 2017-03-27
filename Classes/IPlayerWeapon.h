#pragma once

#include "cocos_custom.h"
#include "Bullet.h"

class IPlayerWeapon
{
public:
	virtual ~IPlayerWeapon() = default;

	virtual std::vector<cocos2d::RefPtr<CBullet>> Fire(Direction direction) = 0;
	virtual bool IsReady() = 0;
	virtual int GetAmmoCount() = 0;

};