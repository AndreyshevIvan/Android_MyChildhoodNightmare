#pragma once

#include "cocos_custom.h"
#include "Bullet.h"
#include "Puppet.h"

class IMapPhysics
{
public:
	virtual bool CanStandOn(const cocos2d::Rect &body) = 0;
	virtual void AddPlayerBullets(std::vector<cocos2d::RefPtr<CBullet>> bullet) = 0;
	virtual void AddEnemy(CPuppet *enemy) = 0;

};