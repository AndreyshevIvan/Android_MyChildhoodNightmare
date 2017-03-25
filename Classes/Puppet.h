#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"
#include "LivingBody.h"

class IPuppeteer;

const float PUPPET_VELOCITY = 200.f;
const float PUPPET_JUMP_VELOCITY = 500.f;

class CPuppet
	: public cocos2d::Node
	, public CLivingBody
{
public:
	bool init();

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
	void MovePuppet();

	cocos2d::PhysicsBody *m_body = nullptr;
	cocos2d::Sprite *m_puppetSprite = nullptr;
	cocos2d::Sprite *m_phantomSprite = nullptr;

	float m_xVelocity = PUPPET_VELOCITY;

	PuppetState m_moveState;
	PuppetState m_jumpState;

};

typedef cocos2d::RefPtr<CPuppet> CPuppetPtr;