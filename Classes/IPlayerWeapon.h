#pragma once

#include "cocos_custom.h"
#include "Bullet.h"

typedef std::vector<cocos2d::RefPtr<CBullet>> Bullets;

class IPlayerWeapon
{
public:
	virtual ~IPlayerWeapon() = default;

	virtual Bullets Fire(Direction direction) = 0;
	virtual int GetAmmoCount() const = 0;
	virtual bool IsInfinity() = 0;

};