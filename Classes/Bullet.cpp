#include "Bullet.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char PISTOL_BULLET_IMG[] = "pistol_bullet.png";
	const char SHOOTGUN_BULLET_IMG[] = "shootgun_bullet.png";
	const char AK_BULLET_IMG[] = "ak_bullet.png";

	const float PISTOL_BULLET_SPEED = 500;
	const float SHOOTGUN_BULLET_SPEED = 600;
	const float AK_BULLET_SPEED = 700;

	const float BULLET_DISTANCE = 400;
	const float CRITICAL_DELTA_TIME = 0.05;
}

cocos2d::RefPtr<CBullet> CBullet::Create()
{
	cocos2d::RefPtr<CBullet> bullet = make_node<CBullet>();
	bullet->setVisible(false);
	return bullet;
}

cocos2d::RefPtr<CBullet> CBullet::CreatePistolBullet()
{
	cocos2d::RefPtr<CBullet> bullet = CBullet::Create();
	bullet->InitBody(PISTOL_BULLET_IMG);
	bullet->SetSpeed(PISTOL_BULLET_SPEED);

	return bullet;
}
cocos2d::RefPtr<CBullet> CBullet::CreateShootgunBullet()
{
	cocos2d::RefPtr<CBullet> bullet = CBullet::Create();
	bullet->InitBody(SHOOTGUN_BULLET_IMG);
	bullet->SetSpeed(SHOOTGUN_BULLET_SPEED);
	return bullet;
}
cocos2d::RefPtr<CBullet> CBullet::CreateAKBullet()
{
	cocos2d::RefPtr<CBullet> bullet = CBullet::Create();
	bullet->InitBody(AK_BULLET_IMG);
	bullet->SetSpeed(AK_BULLET_SPEED);
	return bullet;
}

void CBullet::InitBody(const std::string &spritePath)
{
	m_body = make_node<Sprite>();
	m_body->initWithSpriteFrameName(spritePath);

	addChild(m_body);
}

cocos2d::RefPtr<CBullet> CBullet::CloneAndStart(const Vec2 &position, Direction dir, int demage)
{
	auto newBullet = CBullet::Create();
	newBullet->m_body = make_node<Sprite>();
	newBullet->m_body->initWithSpriteFrame(m_body->getSpriteFrame());
	newBullet->addChild(newBullet->m_body);
	newBullet->setPosition(position);

	float speed = (dir == Direction::RIGHT) ? m_speed : -m_speed;
	newBullet->SetSpeed(speed);
	newBullet->SetDemage(demage);
	newBullet->scheduleUpdate();
	newBullet->setVisible(true);

	return newBullet;
}

bool CBullet::IsDistanceValid()
{
	return (m_distance <= BULLET_DISTANCE);
}

void CBullet::update(float delta)
{
	delta = (delta > CRITICAL_DELTA_TIME) ? 0.f : delta;

	auto position = getPosition();
	auto movement = Vec2(m_speed * delta, 0);

	setPosition(position + movement);
	m_distance += movement.x;
}

void CBullet::SetSpeed(float speed)
{
	m_speed = speed;
}

void CBullet::SetDemage(int demage)
{
	m_demage = demage;
}

int CBullet::GetDemage() const
{
	return m_demage;
}

void CBullet::onExit()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	this->removeAllChildren();
	Node::onExit();
}