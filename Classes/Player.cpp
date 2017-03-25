#include "Player.h"

USING_NS_CC;

namespace
{
	const Size PLAYER_BODY_SIZE = Size(78, 108);
	const PhysicsMaterial PLAYER_MATERIAL = PhysicsMaterial(500, 0, 0.8f);

	const int PLAYER_BODY_BORDER = 1;
	const float PLAYER_BODY_MASS = 50;
	const int PLAYER_COLLISION_BITMASK = 0x08;

	const int PLAYER_HEALTH = 100;
}

void CPlayer::Spawn(const Vec2 &spawnPos)
{
	init();

	InitLivingBody(PLAYER_HEALTH);
	CreatePlayerBody(spawnPos);
	setPosition(spawnPos);
}

void CPlayer::CreatePlayerBody(const Vec2 &spawnPos)
{
	m_puppetSprite = Sprite::create();
	m_puppetSprite->initWithFile("textures/player.png");
	m_puppetSprite->setPosition(spawnPos);
	addChild(m_puppetSprite);

	m_phantomSprite = Sprite::create();
	m_phantomSprite->initWithFile("textures/player.png");
	m_phantomSprite->setVisible(false);
	m_phantomSprite->setPosition(spawnPos);

	m_body = PhysicsBody::createBox(PLAYER_BODY_SIZE, PLAYER_MATERIAL);
	m_body->setRotationEnable(false);
	m_body->setDynamic(true);
	m_body->setMass(PLAYER_BODY_MASS);
	m_body->setContactTestBitmask(true);
	m_body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

	m_phantomSprite->setPhysicsBody(m_body);
	addChild(m_phantomSprite);
}

void CPlayer::PersonalUpdate(float delta)
{
	m_puppetSprite->setPosition(m_phantomSprite->getPosition());
}