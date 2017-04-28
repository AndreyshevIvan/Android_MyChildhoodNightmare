#include "Puppet.h"
#include "IPuppeteer.h"
#include "IMapPhysics.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const float FLYING_SLOWDOWN = 1;
	const float G = 900;
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
	m_runState = m_puppeteer->GetRunState();
	m_isJump = m_puppeteer->GetJumpState();
	m_isFire = m_puppeteer->GetFireState();

	MoveHorizontal(delta);
	MoveVertical(delta);
	PersonalUpdate(delta);
	UpdateInterfaces();

	m_puppeteer->Update(delta);
}

void CPuppet::MoveHorizontal(float elapsedTime)
{
	if (m_runState != RunState::NOT_RUN)
	{
		Vec2 movement = Vec2(m_moveSpeed.x * elapsedTime, 0);
		movement = (m_runState == RunState::RUN_LEFT) ? -movement : movement;
		UpdateDirection(movement.x);

		setPosition(getPosition() + movement);

		if (!m_mapPhysics->CanStandOn(GetRectInWorld()))
		{
			setPosition(getPosition() - movement);
		}
	}
}

void CPuppet::MoveVertical(float elapsedTime)
{
	if (m_isJump && m_jumpState == JumpState::ON_GROUND)
	{
		m_moveSpeed.y = m_jumpSpeed;
	}

	m_moveSpeed.y = m_moveSpeed.y + G * elapsedTime;
	const Vec2 movement = Vec2(0, m_moveSpeed.y * elapsedTime);
	const Vec2 position = getPosition();
	setPosition(position - movement);

	if (!m_mapPhysics->CanStandOn(GetRectInWorld()))
	{
		setPosition(position);
		m_moveSpeed.y = 0;
		m_jumpState = JumpState::ON_GROUND;
	}
	else
	{
		m_jumpState = JumpState::FLY;
	}
}

void CPuppet::UpdateDirection(float movement)
{
	if (movement < 0)
	{
		m_direction = Direction::LEFT;
	}
	else if (movement > 0)
	{
		m_direction = Direction::RIGHT;
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

Rect CPuppet::GetRectInWorld() const
{
	auto rect = getBoundingBox();
	rect.size = rect.size * m_bodyScaleFactor;
	rect.origin = rect.origin - rect.size / 2;

	return rect;
}

void CPuppet::SetPuppeteer(IPuppeteer* puppeteer)
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

bool CPuppet::IsNeedToSwitchWeapon()
{
	return m_puppeteer->GetSwitchWeaponState();
}

void CPuppet::SetAnimation(AnimationPtr animation, bool isLoop)
{
	ActionInterval* runningAnimation = Animate::create(animation);
	if (isLoop)
	{
		runningAnimation = RepeatForever::create(runningAnimation);
	}
	m_puppetSprite->stopAllActions();
	m_puppetSprite->runAction(runningAnimation);
}