#pragma once

#include "cocos_custom.h"
#include "IController.h"

class IPuppeteer
{
public:
	virtual ~IPuppeteer() = default;

	virtual void OnEnter() = 0;
	virtual void Update(float delta) = 0;
	virtual void OnExit() = 0;

	virtual PuppetState GetMoveState() = 0;
	virtual PuppetState GetJumpState() = 0;

	virtual cocos2d::Vec2 GetPuppetPos() = 0;
};