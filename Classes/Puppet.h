#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"
#include "LivingBody.h"
#include "Weapon.h"
#include "AnimationManager.h"

namespace
{
	const float PUPPET_VELOCITY = 200.f;
	const float PUPPET_JUMP_VELOCITY = -500.f;
}

enum class PuppetAnimType
{
	NONE,
	IDLE,
	RUN,
	JUMP,
	DEMAGED,
	KILL,
};

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

	void SetPuppeteer(IPuppeteer* puppeteer);

private:
	void MoveHorizontal(float delta);
	void MoveVertical(float delta);
	void UpdateDirection(float movement);
	void UpdateDirectionalSprites();

	IPuppeteer* m_puppeteer = nullptr;
	std::set<cocos2d::RefPtr<cocos2d::Sprite>> m_directionalSprites;

protected:
	virtual bool PersonalInit() { return true; };
	virtual bool InitBody() { return true; };
	virtual bool InitAnimations() { return true; };

	virtual void PersonalUpdate(float delta) {};
	virtual void UpdateInterfaces() {};
	virtual void Fire() {};

	cocos2d::Rect GetRectInWorld() const;
	void SetAnimation(cocos2d::Sprite* sprite, PuppetAnimType anim, bool isLoop);
	void AddScaleDependentSprite(cocos2d::RefPtr<cocos2d::Sprite> sprite);
	bool IsNeedToSwitchWeapon();

	cocos2d::Sprite* m_puppetSprite = nullptr;
	IMapPhysics* m_mapPhysics;

	cocos2d::Vec2 m_moveSpeed = cocos2d::Vec2(PUPPET_VELOCITY, 0);
	float m_jumpSpeed = PUPPET_JUMP_VELOCITY;
	float m_bodyScaleFactor = 1;

	Direction m_direction;
	RunState m_runState;
	JumpState m_jumpState;
	bool m_isFire = false;
	bool m_isJump = false;
	std::map<PuppetAnimType, AnimationPtr> m_animations;
	PuppetAnimType m_currentAnim = PuppetAnimType::NONE;
};

typedef cocos2d::RefPtr<CPuppet> CPuppetPtr;