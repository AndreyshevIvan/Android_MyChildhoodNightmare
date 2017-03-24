#pragma once

#include "cocos_custom.h"

enum struct PuppetState
{
	FIRE,
	SWITCH_WEAPON,

	JUMP,

	MOVE_RIGHT,
	MOVE_LEFT,

	NONE,
};

namespace
{
	cocos2d::EventDispatcher *getEvents()
	{
		return cocos2d::Director::getInstance()->getEventDispatcher();
	}
}

class IController
{
public:
	virtual bool init() = 0;

	virtual PuppetState GetMoveState() = 0;
	virtual PuppetState GetJumpState() = 0;

	virtual void Update(float delta) = 0;

protected:
	virtual void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) = 0;
	virtual void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) = 0;

	cocos2d::RefPtr<cocos2d::EventListenerKeyboard> m_keyboard;

};