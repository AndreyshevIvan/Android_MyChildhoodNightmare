#pragma once

#include "cocos_custom.h"
#include "Weapons/Bullet.h"
#include "Puppet.h"

class IMapPhysics
{
public:
	virtual ~IMapPhysics() = default;

	virtual void Pause(bool isPause) = 0;

	virtual bool CanStandOn(const cocos2d::Rect &body) = 0;
	virtual bool CanStandOn(const cocos2d::Point &point) = 0;
	virtual bool GetCollideDoorKey(const cocos2d::Rect &body, std::string &doorKey) = 0;

	virtual void AddPlayerBullets(CBulletsPack bullets) = 0;
	virtual void AddEnemy(CPuppetPtr enemy) = 0;
	virtual void AddPlayer(CPuppetPtr player) = 0;

};