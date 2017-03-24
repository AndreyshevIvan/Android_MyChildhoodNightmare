#include "HeroPuppeteer.h"
#include <iostream>

USING_NS_CC;

void CHeroPuppeteer::SetPuppet(CPuppet *hero)
{
	m_hero = hero;
	if (m_hero)
	{
		m_hero->SetPuppeteer(this);
	}
}

PuppetState CHeroPuppeteer::GetMoveState()
{
	return m_controller->GetMoveState();
}

PuppetState CHeroPuppeteer::GetJumpState()
{
	return m_controller->GetJumpState();
}

Vec2 CHeroPuppeteer::GetPuppetPos()
{
	return m_hero->GetPosition();
}

void CHeroPuppeteer::OnEnter()
{
	m_controller = std::unique_ptr<CPlayerController>(new CPlayerController());
	m_controller->init();
}

void CHeroPuppeteer::Update(float delta)
{
	m_controller->Update(delta);
}

void CHeroPuppeteer::OnExit()
{
	m_controller.reset();
}