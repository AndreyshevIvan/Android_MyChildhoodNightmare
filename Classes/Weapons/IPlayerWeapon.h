#pragma once

#include "cocos_custom.h"
#include "Bullet.h"

typedef std::vector<CBulletPtr> CBulletsPack;

class IPlayerWeapon
{
public:
	virtual ~IPlayerWeapon() = default;

	virtual CBulletsPack Fire(Direction direction) = 0;
	virtual int GetAmmoCount() const = 0;
	virtual bool IsInfinity() = 0;

};