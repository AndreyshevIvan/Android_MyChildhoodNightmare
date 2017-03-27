#include "Player.h"
#include "IMapPhysics.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const Size PLAYER_BODY_SIZE = Size(78, 108);

	const int PLAYER_HEALTH = 100;
	const float PLAYER_VELOCITY = 200;

	const std::string PLAYER_IMG = "textures/player.png";
}

void CPlayer::Spawn(const Vec2 &spawnPos)
{
	InitLivingBody(PLAYER_HEALTH);
	InitPlayer();
	InitWeapons();
	setPosition(spawnPos);
}

void CPlayer::InitPlayer()
{
	m_moveSpeed.x = PLAYER_VELOCITY;

	m_puppetSprite = Sprite::create();
	m_puppetSprite->initWithFile(PLAYER_IMG);
	setContentSize(m_puppetSprite->getContentSize());

	addChild(m_puppetSprite);
}

void CPlayer::InitWeapons()
{
	m_pistol = CPistol::Create(this);
	m_shootgun = CShootgun::Create(this);
	m_ak = CAkWeapon::Create(this);

	addChild(m_pistol);
	addChild(m_shootgun);
	addChild(m_ak);

	m_weapons.push_back(std::pair<CWeapon*, WeaponBar*>(m_pistol, nullptr));
	m_weapons.push_back(std::pair<CWeapon*, WeaponBar*>(m_shootgun, nullptr));
	m_weapons.push_back(std::pair<CWeapon*, WeaponBar*>(m_ak, nullptr));

	m_currentWeapon = m_pistol;
}

void CPlayer::InitWeaponBars(WeaponBar *pistolBar, WeaponBar *shootgunBar, WeaponBar *akBar)
{
	for (auto& weapon : m_weapons)
	{
		if (weapon.first == m_pistol)
		{
			weapon.second = pistolBar;
		}
		if (weapon.first == m_shootgun)
		{
			weapon.second = shootgunBar;
		}
		if (weapon.first == m_ak)
		{
			weapon.second = akBar;
		}

		if (weapon.first == m_currentWeapon)
		{
			weapon.second->SetAmmoCount(m_currentWeapon->GetAmmoCount());
		}
	}
}

void CPlayer::PersonalUpdate(float delta)
{
	SwitchWeapon();
	Fire();
}

void CPlayer::Fire()
{
	if (m_isFire && m_currentWeapon->IsReady())
	{
		auto bullets = m_currentWeapon->Fire(m_direction);
		m_mapPhysics->AddPlayerBullets(bullets);
	}
}

// TODO: Улучшить читаемость
void CPlayer::SwitchWeapon()
{
	if (IsNeedToSwitchWeapon())
	{
		for (size_t i = 0; i < m_weapons.size(); i++)
		{
			if (m_weapons[i].first == m_currentWeapon)
			{
				(m_weapons[i].second)->SetVisible(false);
				i = (i == m_weapons.size() - 1) ? 0 : i + 1;
				m_weapons[i].second->SetVisible(true);
				m_currentWeapon = m_weapons[i].first;
				m_weapons[i].second->SetAmmoCount(m_currentWeapon->GetAmmoCount());
				break;
			}
		}
	}
}