#include "Puppet.h"
#include "IPuppeteer.h"
#include "IMapPhysics.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const float FLYING_SLOWDOWN = 1;
	const float G = 900;
	const float CRITICAL_DELTA_TIME = 0.05f;
}

bool CPuppet::init(IMapPhysics *mapPhysic)
{
	m_mapPhysics = mapPhysic;
	return Node::init() && PersonalInit();
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
	delta = (delta > CRITICAL_DELTA_TIME) ? 0.f : delta;

	m_runState = m_puppeteer->GetRunState();
	m_isJump = m_puppeteer->GetJumpState();
	m_isFire = m_puppeteer->GetFireState();

	MoveHorizontal(delta);
	MoveVertical(delta);
	UpdateDirectionalSprites();
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

		setPosition(GetCenterInWorld() + movement);

		if (!m_mapPhysics->CanStandOn(GetRectInWorld()))
		{
			setPosition(GetCenterInWorld() - movement);
		}
		if (m_jumpState != JumpState::FLY)
		{
			SetAnimation(m_puppetSprite, PuppetAnimType::RUN, true);
		}
	}
	else if (m_jumpState == JumpState::ON_GROUND)
	{
		SetAnimation(m_puppetSprite, PuppetAnimType::IDLE, true);
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
	const Vec2 position = GetCenterInWorld();
	setPosition(position - movement);

	if (!m_mapPhysics->CanStandOn(GetRectInWorld()))
	{
		setPosition(position);
		m_moveSpeed.y = 0;
		m_jumpState = JumpState::ON_GROUND;
	}
	else
	{
		SetAnimation(m_puppetSprite, PuppetAnimType::JUMP, true);
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
void CPuppet::UpdateDirectionalSprites()
{
	auto update_scale = [&](RefPtr<Sprite> sprite) {
		auto scale = sprite->getScaleX();
		if ((m_direction == Direction::LEFT && scale > 0) ||
			(m_direction == Direction::RIGHT && scale < 0))
		{
			sprite->setScaleX(-1 * scale);
		}
	};

	std::for_each(m_directionalSprites.begin(), m_directionalSprites.end(), update_scale);
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

void CPuppet::SetAnimation(cocos2d::Sprite* sprite, PuppetAnimType anim, bool isLoop)
{
	auto animation = m_animations.find(anim);
	if (animation == m_animations.end() || m_currentAnim == anim)
	{
		return;
	}

	ActionInterval* runningAnimation = Animate::create(animation->second);
	if (isLoop)
	{
		runningAnimation = RepeatForever::create(runningAnimation);
	}
	sprite->stopAllActions();
	sprite->runAction(runningAnimation);
	m_currentAnim = anim;
}

void CPuppet::AddScaleDependentSprite(cocos2d::RefPtr<cocos2d::Sprite> sprite)
{
	m_directionalSprites.insert(sprite);
}