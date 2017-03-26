#pragma once

#include "cocos_custom.h"

enum struct RunState
{
	NOT_RUN,
	RUN_LEFT,
	RUN_RIGHT,
};

enum struct JumpState
{
	FLY,
	ON_GROUND,
};

class CPlayerController
{
public:
	bool init();
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	RunState GetRunState();
	bool GetJumpState();
	void ResetStates();

	void MoveLeft();
	void MoveRight();
	void Jump();
	void Fire();
	void Reload();

private:
	bool m_pressedJump = false;
	bool m_pressedKeyA = false;
	bool m_pressedKeyD = false;

	RunState m_runState;
	JumpState m_jumpState;
};
