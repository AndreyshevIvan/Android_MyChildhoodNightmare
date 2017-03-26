#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"
#include "LivingBody.h"
#include "IMapPhysics.h"

namespace
{
	const float PUPPET_VELOCITY = 200.f;
	const float PUPPET_JUMP_VELOCITY = 500.f;
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
	void MoveVertical(float delta);
	void UpdateGravity(float delta, bool isNeedJump);
	cocos2d::Rect GetRectInWorld();

	cocos2d::Sprite *m_puppetSprite = nullptr;
	IMapPhysics *m_mapPhysics;

	float m_moveSpeed = PUPPET_VELOCITY;
	float m_jumpSpeed = 0;

	RunState m_runState;
	JumpState m_jumpState;
};

typedef cocos2d::RefPtr<CPuppet> CPuppetPtr;