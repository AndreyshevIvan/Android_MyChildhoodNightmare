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
	const string PLAYER_RUN = "player_run.png";
	const string PLAYER_IDLE = "player_idle.png";
	const string PLAYER_JUMP = "player_jump.png";
}

bool CPlayer::PersonalInit()
{
	InitLivingBody(PLAYER_HEALTH);

	return (InitAnimations() && InitBody() && InitWeapons());
}

void CPlayer::Spawn(const Vec2 &spawnPos)
{
	setPosition(spawnPos);
}

bool CPlayer::InitBody()
{
	m_moveSpeed.x = PLAYER_VELOCITY;
	m_puppetSprite = Sprite::create();
	setContentSize(PLAYER_SIZE);

	AddScaleDependentSprite(m_puppetSprite);
	addChild(m_puppetSprite);

	return true;
}
bool CPlayer::InitWeapons()
{
	if (!(m_pistol = CPistol::Create(this)) ||
		!(m_shootgun = CShootgun::Create(this)) ||
		!(m_ak = CAkWeapon::Create(this)))
	{
		return false;
	}

	addChild(m_pistol);
	addChild(m_shootgun);
	addChild(m_ak);

	m_weapons.resize(WEAPONS_COUNT);
	m_weapons[Weapons::PISTOL] = std::make_pair(m_pistol, nullptr);
	m_weapons[Weapons::SHOOTGUN] = std::make_pair(m_shootgun, nullptr);
	m_weapons[Weapons::AK] = std::make_pair(m_ak, nullptr);

	m_currentWeapon = m_pistol;

	return true;
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
bool CPlayer::InitAnimations()
{
	try
	{
		auto runAnim = CAnimManager::CreateAnim(PLAYER_RUN, PLAYER_SIZE, 6);
		auto idleAnim = CAnimManager::CreateAnim(PLAYER_IDLE, PLAYER_SIZE, 6);
		auto jumpAnim = CAnimManager::CreateAnim(PLAYER_JUMP, PLAYER_SIZE, 6);
		if (!runAnim || !idleAnim || !jumpAnim)
		{
			return false;
		}

		m_animations.insert(make_pair(PuppetAnimType::RUN, runAnim));
		m_animations.insert(make_pair(PuppetAnimType::IDLE, idleAnim));
		m_animations.insert(make_pair(PuppetAnimType::JUMP, jumpAnim));
	}
	catch (const std::exception &)
	{
		return false;
	}

	return true;
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