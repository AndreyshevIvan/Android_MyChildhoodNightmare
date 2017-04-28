#include "Enemies/EnemyShadow.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const int ENEMY_HEALTH = 100;
	const std::string ENEMY_IMG = "enemy.png";
}

bool CEnemyShadow::InitBody()
{
	InitLivingBody(ENEMY_HEALTH);

	m_puppetSprite = make_node<Sprite>();
	m_puppetSprite->initWithSpriteFrameName(ENEMY_IMG);
	setContentSize(m_puppetSprite->getContentSize());

	addChild(m_puppetSprite);

	return true;
}

bool CEnemyShadow::InitTactics()
{
	return true;
}

void CEnemyShadow::UpdateWorldInfo(float delta)
{

}
void CEnemyShadow::ChooseTactic()
{

}
void CEnemyShadow::DoTactic(float delta)
{

}