#include "PlayerController.h"

USING_NS_CC;

const int FIXED_EVENT_PRIORITY = 100;

namespace
{
	cocos2d::EventDispatcher *getEvents()
	{
		return cocos2d::Director::getInstance()->getEventDispatcher();
	}
}

bool CPlayerController::init()
{
	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = CC_CALLBACK_2(CPlayerController::OnKeyPressed, this);
	keyboard->onKeyReleased = CC_CALLBACK_2(CPlayerController::OnKeyReleased, this);
	getEvents()->addEventListenerWithFixedPriority(keyboard, FIXED_EVENT_PRIORITY);

	return true;
}

RunState CPlayerController::GetRunState()
{
	return m_runState;
}

bool CPlayerController::GetJumpState()
{
	return m_pressedJump;
}

void CPlayerController::MoveLeft()
{
	m_pressedKeyA = true;
}

void CPlayerController::MoveRight()
{
	m_pressedKeyD = true;
}

void CPlayerController::Jump()
{
	m_pressedJump = true;
}

void CPlayerController::Fire()
{

}

void CPlayerController::Reload()
{

}

void CPlayerController::ResetStates()
{
	m_runState = RunState::NOT_RUN;

	if (m_pressedKeyA)
	{
		m_runState = RunState::RUN_LEFT;
	}
	if (m_pressedKeyD)
	{
		m_runState = RunState::RUN_RIGHT;
	}

	m_pressedJump = false;
	m_pressedKeyA = false;
	m_pressedKeyD = false;
}

void CPlayerController::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	(void)event;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		m_pressedJump = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_pressedKeyA = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_pressedKeyD = true;
		break;
	default:
		return;
	}
}

void CPlayerController::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	(void)event;

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		m_pressedJump = false;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_pressedKeyA = false;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_pressedKeyD = false;
		break;
	default:
		return;
	}
}