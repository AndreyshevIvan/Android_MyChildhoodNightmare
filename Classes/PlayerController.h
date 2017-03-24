#pragma once

#include "IController.h"
#include <iostream>

class CPlayerController : public IController
{
public:
	bool init() override;
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;

	PuppetState GetMoveState() override;
	PuppetState GetJumpState() override;

	void Update(float delta) override;

private:
	bool m_pressedKeySpace = false;
	bool m_pressedKeyA = false;
	bool m_pressedKeyD = false;

	PuppetState m_moveState = PuppetState::NONE;
	PuppetState m_jumpState = PuppetState::NONE;
	PuppetState m_weaponState = PuppetState::NONE;
};
