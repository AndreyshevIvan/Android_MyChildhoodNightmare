#include "Enemy.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const int ENEMY_HEALTH = 100;
	const std::string ENEMY_IMG = "enemy.png";
}

void CEnemy::Spawn(const Vec2 &position)
{
	InitLivingBody(ENEMY_HEALTH);
	InitEnemy();
	setPosition(position);
}

void CEnemy::InitEnemy()
{
	m_puppetSprite = make_node<Sprite>();
	m_puppetSprite->initWithSpriteFrameName(ENEMY_IMG);
	setContentSize(m_puppetSprite->getContentSize());

	addChild(m_puppetSprite);
}

void CEnemy::PersonalUpdate(float delta)
{

}