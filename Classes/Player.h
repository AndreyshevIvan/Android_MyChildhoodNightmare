#pragma once

#include "Puppet.h"
#include "cocos_custom.h"

class CPlayer
	: public CPuppet
{
public:
	void Spawn(const cocos2d::Vec2 &spawnPos);

protected:
	void PersonalUpdate(float delta) override;

private:
	void CreatePlayerBody(const cocos2d::Vec2 &spawnPos);

};