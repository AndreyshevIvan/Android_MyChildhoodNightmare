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

	m_pistol = CWeapon::CreatePistol();
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
	Fire();
}

void CPlayer::Fire()
{
	if (m_isFire)
	{

	}
}