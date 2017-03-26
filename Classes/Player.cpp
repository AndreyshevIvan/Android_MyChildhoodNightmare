#include "Player.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const Size PLAYER_BODY_SIZE = Size(78, 108);

	const int PLAYER_HEALTH = 100;
	const float PLAYER_VELOCITY = 200;
}

void CPlayer::Spawn(const Vec2 &spawnPos)
{
	InitLivingBody(PLAYER_HEALTH);
	InitPlayer(spawnPos);
	setPosition(spawnPos);

	m_pistol = CPistol::Create(this);
	m_shootgun = CShootgun::Create(this);
	m_ak = CAkWeapon::Create(this);

	addChild(m_pistol);
	addChild(m_shootgun);
	addChild(m_ak);

	m_weapons.push_back(m_pistol);
	m_weapons.push_back(m_shootgun);
	m_weapons.push_back(m_ak);

	m_currentWeapon = m_pistol;
}

void CPlayer::InitPlayer(const Vec2 &spawnPos)
{
	m_moveSpeed.x = PLAYER_VELOCITY;

	m_puppetSprite = Sprite::create();
	m_puppetSprite->initWithFile("textures/player.png");
	m_puppetSprite->setContentSize(PLAYER_BODY_SIZE);
	setContentSize(PLAYER_BODY_SIZE);

	addChild(m_puppetSprite);
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

void CPlayer::SwitchWeapon()
{
	if (IsNeedToSwitchWeapon())
	{
		for (size_t i = 0; i < m_weapons.size(); i++)
		{
			if (m_weapons[i] == m_currentWeapon)
			{
				i = (i == m_weapons.size() - 1) ? 0 : i + 1;
				m_currentWeapon = m_weapons[i];
				break;
			}
		}
	}
}