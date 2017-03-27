#include "EnemyPuppeteer.h"
#include <iostream>

USING_NS_CC;

void CEnemyPuppeteer::SetPuppet(CPuppet *enemy)
{
	m_enemy = enemy;
	if (m_enemy)
	{
		m_enemy->SetPuppeteer(this);
	}
}

RunState CEnemyPuppeteer::GetMoveState()
{
	return RunState::NOT_RUN;
}

bool CEnemyPuppeteer::CheckJumpState()
{
	return false;
}

bool CEnemyPuppeteer::GetFireState()
{
	return false;
}

bool CEnemyPuppeteer::GetSwitchWeaponState()
{
	return false;
}

Vec2 CEnemyPuppeteer::GetPuppetPos()
{
	return m_enemy->GetPosition();
}

void CEnemyPuppeteer::OnEnter()
{

}

void CEnemyPuppeteer::Update(float delta)
{

}

void CEnemyPuppeteer::OnExit()
{

}