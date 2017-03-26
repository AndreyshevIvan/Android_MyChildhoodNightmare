#pragma once

#include "cocos_custom.h"
#include "PlayerController.h"

class IPuppeteer
{
public:
	virtual ~IPuppeteer() = default;

	virtual void OnEnter() = 0;
	virtual void Update(float delta) = 0;
	virtual void OnExit() = 0;

	virtual RunState GetMoveState() = 0;
	virtual bool CheckJumpState() = 0;
	virtual bool GetFireState() = 0;
	virtual bool GetSwitchWeaponState() = 0;

	virtual cocos2d::Vec2 GetPuppetPos() = 0;
};