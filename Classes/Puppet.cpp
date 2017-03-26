#include "Puppet.h"
#include "IPuppeteer.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const float FLYING_SLOWDOWN = 1;
	const float G = 1200;
}

bool CPuppet::init(IMapPhysics *mapPhysic)
{
	m_mapPhysics = mapPhysic;
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
	m_runState = m_puppeteer->GetMoveState();
	bool isNeedJump = m_puppeteer->GetJumpState();

	auto rect = getBoundingBox();
	std::cout << "MinX: " << rect.getMinX() << " MinY: " << rect.getMinY() << " MaxX: " << rect.getMaxX() << " MaxY: " << rect.getMaxY() << std::endl;

	MoveVertical(delta);
	UpdateGravity(delta, isNeedJump);

	m_puppeteer->Update(delta);
	PersonalUpdate(delta);
}

void CPuppet::MoveVertical(float elapsedTime)
{
	if (m_runState != RunState::NOT_RUN)
	{
		Vec2 movement = Vec2(m_moveSpeed * elapsedTime, 0);
		movement = (m_runState == RunState::RUN_LEFT) ? -movement : movement;

		setPosition(getPosition() + movement);

		if (!m_mapPhysics->CanStandOn(GetRectInWorld()))
		{
			setPosition(getPosition() - movement);
		}
	}
}

void CPuppet::UpdateGravity(float elapsedTime, bool isNeedJump)
{
	if (isNeedJump && m_jumpState == JumpState::ON_GROUND)
	{
		m_jumpSpeed -= 500;
	}

	Vec2 movement = Vec2(0, m_jumpSpeed);
	m_jumpSpeed = m_jumpSpeed + G * elapsedTime;
	movement.y = m_jumpSpeed * elapsedTime;

	setPosition(getPosition() - movement);

	if (m_mapPhysics->CanStandOn(GetRectInWorld()))
	{
		m_jumpState = JumpState::FLY;
	}
	else
	{
		setPosition(getPosition() + movement);
		m_jumpSpeed = 0;

		if (movement.y > 0)
		{
			m_jumpState = JumpState::ON_GROUND;
		}
	}
}

Vec2 CPuppet::GetCenterInWorld() const
{
	Vec2 localCenter(0, 0);
	return convertToWorldSpace(localCenter);
}

Vec2 CPuppet::GetPosition() const
{
	return getPosition();
}

Rect CPuppet::GetRectInWorld()
{
	auto rect = getBoundingBox();
	rect.size = rect.size * 0.9f;
	rect.origin = rect.origin - rect.size / 2;

	return rect;
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