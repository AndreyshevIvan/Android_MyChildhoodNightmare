#pragma once

#include "Puppet.h"
#include "cocos_custom.h"
#include "UILayer.h"

class CPlayer
	: public CPuppet
{
public:
	void Spawn(const cocos2d::Vec2 &spawnPos) override;
	void InitWeaponBars(WeaponBar *pistolBar, WeaponBar *shootgunBar, WeaponBar *akBar);

protected:
	void PersonalUpdate(float delta) override;

private:
	void InitPlayer();
	void InitWeapons();

	void Fire() override;
	void SwitchWeapon();

	CUILayer m_UIcontroller;

	IPlayerWeapon *m_currentWeapon = nullptr;
	cocos2d::RefPtr<CWeapon> m_pistol = nullptr;
	cocos2d::RefPtr<CWeapon> m_shootgun = nullptr;
	cocos2d::RefPtr<CWeapon> m_ak = nullptr;

	std::vector<std::pair<CWeapon*, WeaponBar*>> m_weapons;
};