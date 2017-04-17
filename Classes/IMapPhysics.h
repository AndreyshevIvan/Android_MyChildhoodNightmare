#pragma once

#include "cocos_custom.h"
#include "Bullet.h"
#include "Puppet.h"

class IMapPhysics
{
public:
	virtual ~IMapPhysics() = default;

	virtual bool CanStandOn(const cocos2d::Rect &body) = 0;
	virtual void AddPlayerBullets(Bullets bullets) = 0;
	virtual void AddEnemy(CPuppet *enemy) = 0;

};