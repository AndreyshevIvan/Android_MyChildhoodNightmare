#include "Puppet.h"
#include "IPuppeteer.h"
#include <iostream>

USING_NS_CC;

bool CPuppet::init()
{
	return Node::init();
}

void CPuppet::onEnter()
{
	Node::onEnter();
	this->scheduleUpdate();
	if (m_puppeteer)
	{
		m_puppeteer->OnEnter();
	}
}

void CPuppet::onExit()
{
	unscheduleUpdate();
	if (m_puppeteer)
	{
		m_puppeteer->OnExit();
	}
	Node::onExit();
}

void CPuppet::update(float delta)
{
	m_moveState = m_puppeteer->GetMoveState();
	m_jumpState = m_puppeteer->GetJumpState();

	MovePuppet();

	m_puppeteer->Update(delta);
	PersonalUpdate(delta);
}

void CPuppet::MovePuppet()
{
	auto currVelocity = m_body->getVelocity();

	switch (m_moveState)
	{
	case PuppetState::MOVE_RIGHT:
		m_body->setVelocity(Vec2(0, currVelocity.y) + Vec2(m_xVelocity, 0));
		break;
	case PuppetState::MOVE_LEFT:
		m_body->setVelocity(Vec2(0, currVelocity.y) + Vec2(-m_xVelocity, 0));
		break;
	default:
		break;
	}

	if (m_jumpState == PuppetState::JUMP)
	{
		m_body->setVelocity(Vec2(currVelocity.x, PUPPET_JUMP_VELOCITY));
	}
}

Vec2 CPuppet::GetCenterInWorld() const
{
	Vec2 localCenter(0, 0);
	return convertToWorldSpace(localCenter);
}

Vec2 CPuppet::GetPosition() const
{
	if (m_body)
	{
		return m_body->getPosition();
	}

	return Vec2::ZERO;
}

void CPuppet::SetPuppeteer(IPuppeteer *puppeteer)
{
	if (m_puppeteer && isRunning())
	{
		m_puppeteer->OnExit();
	}
	m_puppeteer = puppeteer;
	if (m_puppeteer && isRunning())
	{
		m_puppeteer->OnEnter();
	}
}