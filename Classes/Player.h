#pragma once

#include "Puppet.h"
#include "cocos_custom.h"
#include "UILayer.h"

namespace
{
	enum Weapons
	{
		PISTOL,
		SHOOTGUN,
		AK,
	};

	const int WEAPONS_COUNT = (int)Weapons::AK + 1;
}

typedef std::vector<std::pair<CWeapon*, UILayer::WeaponBar*>> WeaponsContainer;

class CPlayer : public CPuppet
{
public:
	void InitPlayer();
	void Spawn(const cocos2d::Vec2 &spawnPos) override;
	void InitWeaponBars(UILayer::WeaponBar *pistolBar, UILayer::WeaponBar *shootgunBar, UILayer::WeaponBar *akBar);

protected:
	void InitAnimations() override;
	void PersonalUpdate(float delta) override;

private:
	void InitBody();
	void InitWeapons();

	void Fire() override;
	void SwitchWeapon();
	void UpdateWeaponBar();

	UILayer::WeaponBar *m_currentWeaponBar;
	IPlayerWeapon *m_currentWeapon = nullptr;
	cocos2d::RefPtr<CWeapon> m_pistol = nullptr;
	cocos2d::RefPtr<CWeapon> m_shootgun = nullptr;
	cocos2d::RefPtr<CWeapon> m_ak = nullptr;

	WeaponsContainer m_weapons;
};