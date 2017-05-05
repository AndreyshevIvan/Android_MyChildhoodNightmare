#pragma once

#include "Puppet.h"
#include "cocos_custom.h"
#include "UILayer.h"

using namespace UILayer;

namespace
{
	enum Weapons
	{
		PISTOL,
		SHOOTGUN,
		AK,
	};

	const int WEAPONS_COUNT = Weapons::AK + 1;
}

typedef std::vector<std::pair<CWeapon*, WeaponBar*>> WeaponsContainer;

class CPlayer : public CPuppet
{
public:
	void Spawn(const cocos2d::Vec2 &spawnPos) override;
	void InitWeaponBars(WeaponBar *pistolBar, WeaponBar *shootgunBar, WeaponBar *akBar);

	std::function<void(const std::string &doorKey)> onDoorContact;

protected:
	bool PersonalInit() override;
	bool InitBody() override;
	bool InitAnimations() override;

	void PersonalUpdate(float delta) override;

private:
	bool InitWeapons();

	void Fire() override;
	void SwitchWeapon();
	void CheckDoorsContact();
	void UpdateWeaponBar();

	WeaponBar *m_currentWeaponBar;
	IPlayerWeapon *m_currentWeapon = nullptr;
	cocos2d::RefPtr<CWeapon> m_pistol = nullptr;
	cocos2d::RefPtr<CWeapon> m_shootgun = nullptr;
	cocos2d::RefPtr<CWeapon> m_ak = nullptr;

	WeaponsContainer m_weapons;
};