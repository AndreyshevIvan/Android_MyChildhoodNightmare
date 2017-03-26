#pragma once

#include "Puppet.h"
#include "cocos_custom.h"
#include "UILayer.h"

class CPlayer
	: public CPuppet
{
public:
	void Spawn(const cocos2d::Vec2 &spawnPos);

protected:
	void PersonalUpdate(float delta) override;

private:
	void InitPlayer(const cocos2d::Vec2 &spawnPos);
	void Fire();

	CUILayer m_UIcontroller;
	cocos2d::RefPtr<CWeapon> m_pistol = nullptr;

};