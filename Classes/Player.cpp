#include "Player.h"
#include "IMapPhysics.h"
#include "GameUI.h"
#include <iostream>

USING_NS_CC;
using namespace UILayer;

namespace
{
	const int PLAYER_HEALTH = 100;
	const float PLAYER_VELOCITY = 200;

	const Size PLAYER_SIZE = Size(53, 75);
	const string PLAYER_JUMP = "player_2.png";
}

void CPlayer::InitPlayer()
{
	InitLivingBody(PLAYER_HEALTH);
	InitAnimations();
	InitBody();
	InitWeapons();
}

void CPlayer::Spawn(const Vec2 &spawnPos)
{
	setPosition(spawnPos);
}

void CPlayer::InitBody()
{
	m_moveSpeed.x = PLAYER_VELOCITY;
	m_puppetSprite = Sprite::create();
	SetAnimation(m_animations.at(PuppetAnimType::JUMP));
	setContentSize(PLAYER_SIZE);
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

	m_weapons.resize(WEAPONS_COUNT);
	m_weapons[Weapons::PISTOL] = std::make_pair(m_pistol, nullptr);
	m_weapons[Weapons::SHOOTGUN] = std::make_pair(m_shootgun, nullptr);
	m_weapons[Weapons::AK] = std::make_pair(m_ak, nullptr);

	m_currentWeapon = m_pistol;
}
void CPlayer::InitWeaponBars(WeaponBar *pistolBar, WeaponBar *shootgunBar, WeaponBar *akBar)
{
	m_weapons[Weapons::PISTOL].second = pistolBar;
	m_weapons[Weapons::SHOOTGUN].second = shootgunBar;
	m_weapons[Weapons::AK].second = akBar;

	pistolBar->SetInfinity(true);
	m_currentWeaponBar = pistolBar;
	UpdateWeaponBar();
}
void CPlayer::InitAnimations()
{
	auto jumpAnim = CAnimManager::CreateAnim(PLAYER_JUMP, PLAYER_SIZE, 3);

	m_animations.insert(make_pair(PuppetAnimType::JUMP, jumpAnim));
}

void CPlayer::PersonalUpdate(float delta)
{
	CheckDoorsContact();
	SwitchWeapon();
	Fire();
}

void CPlayer::CheckDoorsContact()
{
	string doorKey;

	if (m_mapPhysics->GetCollideDoorKey(GetRectInWorld(), doorKey))
	{
		onDoorContact(doorKey);
	}
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

	const int ammoCount = m_currentWeapon->GetAmmoCount();
	m_currentWeaponBar->Update(ammoCount);
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
	{
		lastBar->SetVisible(false);
	}
	m_currentWeaponBar = newBar;
	UpdateWeaponBar();
}