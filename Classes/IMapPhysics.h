#pragma once

#include "cocos_custom.h"
#include "Bullet.h"
#include "Puppet.h"

class IMapPhysics
{
public:
	virtual ~IMapPhysics() = default;

	virtual bool CanStandOn(const cocos2d::Rect &body) = 0;
	virtual void AddPlayerBullets(CBulletsPack bullets) = 0;
	virtual void AddEnemy(CPuppetPtr enemy) = 0;
	virtual void AddPlayer(CPuppetPtr player) = 0;
	virtual void Pause(bool isPause) = 0;

};