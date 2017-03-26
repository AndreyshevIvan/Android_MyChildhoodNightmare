#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"
#include "LivingBody.h"
#include "IMapPhysics.h"
#include "Weapon.h"

namespace
{
	const float PUPPET_VELOCITY = 200.f;
	const float PUPPET_JUMP_VELOCITY = -500.f;
}

class IPuppeteer;

class CPuppet
	: public cocos2d::Node
	, public CLivingBody
{
public:
	bool init(IMapPhysics *mapPhysic);

	void onEnter() override;
	void onExit() override;
	void update(float delta) override;

	cocos2d::Vec2 GetCenterInWorld()const;
	cocos2d::Vec2 GetPosition()const;

	void SetPuppeteer(IPuppeteer *puppeteer);

private:
	IPuppeteer *m_puppeteer = nullptr;

protected:
	virtual void PersonalUpdate(float delta) {};
	void MoveHorizontal(float delta);
	void MoveVertical(float delta);
	cocos2d::Rect GetRectInWorld() const;

	cocos2d::Sprite *m_puppetSprite = nullptr;
	IMapPhysics *m_mapPhysics;

	cocos2d::Vec2 m_moveSpeed = cocos2d::Vec2(PUPPET_VELOCITY, 0);
	float m_jumpSpeed = PUPPET_JUMP_VELOCITY;
	float m_bodyScaleFactor = 1;

	RunState m_runState;
	JumpState m_jumpState;
	bool m_isFire = false;
	bool m_isJump = false;
};

typedef cocos2d::RefPtr<CPuppet> CPuppetPtr;