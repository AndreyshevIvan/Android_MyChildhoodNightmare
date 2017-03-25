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

void CHeroPuppeteer::SetController(CPlayerController *controller)
{
	m_controller = std::shared_ptr<CPlayerController>(controller);
	m_controller->init();
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

std::shared_ptr<CPlayerController> CHeroPuppeteer::GetController()
{
	return m_controller;
}

void CHeroPuppeteer::OnEnter()
{

}

void CHeroPuppeteer::Update(float delta)
{
	m_controller->Update(delta);
}

void CHeroPuppeteer::OnExit()
{
	m_controller.reset();
}