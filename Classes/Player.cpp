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

	m_weapons.push_back(WeaponsContainer::value_type(m_pistol, nullptr));
	m_weapons.push_back(WeaponsContainer::value_type(m_shootgun, nullptr));
	m_weapons.push_back(WeaponsContainer::value_type(m_ak, nullptr));

	m_currentWeapon = m_pistol;
}

void CPlayer::InitWeaponBars(WeaponBar *pistolBar, WeaponBar *shootgunBar, WeaponBar *akBar)
{
	WeaponBar *currentBar = nullptr;

	for (auto& weapon : m_weapons)
	{
		if (weapon.first == m_pistol)
		{
			weapon.second = pistolBar;
			currentBar = pistolBar;
		}
		if (weapon.first == m_shootgun)
		{
			weapon.second = shootgunBar;
		}
		if (weapon.first == m_ak)
		{
			weapon.second = akBar;
		}
	}

	m_currentWeaponBar = currentBar;
	UpdateWeaponBar();
}

void CPlayer::PersonalUpdate(float delta)
{
	SwitchWeapon();
	Fire();
}

void CPlayer::Fire()
{
	if (!m_isFire)
	{
		return;
	}

	auto bullets = m_currentWeapon->Fire(m_direction);
	m_mapPhysics->AddPlayerBullets(bullets);
	UpdateWeaponBar();
}

void CPlayer::UpdateWeaponBar()
{
	if (!m_currentWeaponBar)
	{
		return;
	}

	CUILayer::UpdateWeaponBar(m_currentWeaponBar, m_currentWeapon->GetAmmoCount());
}

void CPlayer::SwitchWeapon()
{
	if (!IsNeedToSwitchWeapon())
	{
		return;
	}

	WeaponBar* lastBar = nullptr;
	WeaponBar* newBar = nullptr;

	for (size_t weaponNum = 0; weaponNum < m_weapons.size(); weaponNum++)
	{
		if (m_weapons[weaponNum].first != m_currentWeapon)
		{
			continue;
		}
		
		bool isPickLastWeapon = (weaponNum == m_weapons.size() - 1);
		int nextWeaponNum = isPickLastWeapon ? 0 : weaponNum + 1;

		lastBar = m_weapons[weaponNum].second;
		newBar = m_weapons[nextWeaponNum].second;
		m_currentWeapon = m_weapons[nextWeaponNum].first;
		break;
	}

	if (lastBar)
		lastBar->SetVisible(false);
	m_currentWeaponBar = newBar;
	UpdateWeaponBar();
}