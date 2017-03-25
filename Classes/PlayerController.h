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


class CPlayerController
{
public:
	bool init();
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	PuppetState GetMoveState();
	PuppetState GetJumpState();

	void Update(float delta);

	void SetMoveButtons(bool isLeft, bool isRight);

private:
	bool m_pressedKeySpace = false;
	bool m_pressedKeyA = false;
	bool m_pressedKeyD = false;

	PuppetState m_moveState = PuppetState::NONE;
	PuppetState m_jumpState = PuppetState::NONE;
	PuppetState m_weaponState = PuppetState::NONE;
};
