#include "Enemies/Enemy.h"
#include "IMapPhysics.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const float BOTTOM_HAND_MARGIN = 10;
}

bool CEnemy::PersonalInit()
{
	return (InitBody() && InitAnimations() && InitTactics());
}

void CEnemy::Spawn(const Vec2 &position)
{
	setPosition(position);
}

void CEnemy::PersonalUpdate(float delta)
{
	UpdateTriggers();
	UpdateWorldInfo(delta);
	ChooseTactic();
	DoTactic(delta);
}

void CEnemy::UpdateTriggers()
{
	const float &leftPosX = getPosition().x - getContentSize().width / 2;
	const float &rightPosX = getPosition().x + getContentSize().width / 2;
	const float &bottomPosY = getPosition().y - getContentSize().height / 2;

	m_handBottomLeft.setPoint(leftPosX, bottomPosY - BOTTOM_HAND_MARGIN);
	m_handBottomRight.setPoint(rightPosX, bottomPosY - BOTTOM_HAND_MARGIN);
	m_handMiddleLeft.setPoint(leftPosX, getPosition().y);
	m_handMiddleRight.setPoint(rightPosX, getPosition().y);
}

bool CEnemy::IsTriggerML()
{
	return m_mapPhysics->CanStandOn(m_handMiddleLeft);
}
bool CEnemy::IsTriggerMR()
{
	return m_mapPhysics->CanStandOn(m_handMiddleRight);
}
bool CEnemy::IsTriggerBL()
{
	return m_mapPhysics->CanStandOn(m_handMiddleLeft);
}
bool CEnemy::IsTriggerBR()
{
	return m_mapPhysics->CanStandOn(m_handMiddleRight);
}
bool CEnemy::IsCatchTarget()
{
	return false;
}