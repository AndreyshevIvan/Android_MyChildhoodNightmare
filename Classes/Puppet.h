#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"
#include "LivingBody.h"
#include "Weapon.h"
#include "AnimationManager.h"

namespace
{
	enum class AnimType
	{
		IDLE,
		RUN,
		JUMP,

		PURSUITE,
	};

	const float PUPPET_VELOCITY = 200.f;
	const float PUPPET_JUMP_VELOCITY = -500.f;
}

class IPuppeteer;
class IMapPhysics;

class CPuppet
	: public cocos2d::Node
	, public CLivingBody
{
public:
	bool init(IMapPhysics *mapPhysics);
	virtual void Spawn(const cocos2d::Vec2 &position) {};

	void onEnter() override;
	void onExit() override;
	void update(float delta) override;

	cocos2d::Vec2 GetCenterInWorld() const;
	cocos2d::Vec2 GetPosition() const;

	void SetPuppeteer(IPuppeteer *puppeteer);

private:
	cocos2d::Rect GetRectInWorld() const;
	void MoveHorizontal(float delta);
	void MoveVertical(float delta);
	void UpdateDirection(float movement);

	IPuppeteer *m_puppeteer = nullptr;

protected:
	virtual void InitAnims() {};
	virtual void PersonalUpdate(float delta) {};
	virtual void UpdateInterfaces() {};
	virtual void Fire() {};

	void SetAnimation(cocos2d::Animation* animation, bool isLoop = true);
	bool IsNeedToSwitchWeapon();

	cocos2d::Sprite *m_puppetSprite = nullptr;
	IMapPhysics *m_mapPhysics;

	cocos2d::Vec2 m_moveSpeed = cocos2d::Vec2(PUPPET_VELOCITY, 0);
	float m_jumpSpeed = PUPPET_JUMP_VELOCITY;
	float m_bodyScaleFactor = 1;

	Direction m_direction;
	RunState m_runState;
	JumpState m_jumpState;
	bool m_isFire = false;
	bool m_isJump = false;
	std::map<AnimType, cocos2d::RefPtr<cocos2d::Animation>> m_animations;
};

typedef cocos2d::RefPtr<CPuppet> CPuppetPtr;