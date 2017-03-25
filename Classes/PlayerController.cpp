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

PuppetState CPlayerController::GetMoveState()
{
	return m_moveState;
}

PuppetState CPlayerController::GetJumpState()
{
	return m_jumpState;
}

void CPlayerController::SetMoveButtons(bool isLeft, bool isRight)
{
	m_pressedKeyD = isRight;
	m_pressedKeyA = isLeft;
}


void CPlayerController::Update(float delta)
{
	m_moveState = PuppetState::NONE;
	m_jumpState = PuppetState::NONE;

	if (m_pressedKeySpace)
	{
		m_jumpState = PuppetState::JUMP;
	}
	if (m_pressedKeyD)
	{
		m_moveState = PuppetState::MOVE_RIGHT;
	}
	if (m_pressedKeyA)
	{
		m_moveState = PuppetState::MOVE_LEFT;
	}
}

void CPlayerController::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	(void)event;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (!m_pressedKeySpace)
		{
			m_pressedKeySpace = true;
		}
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
		m_pressedKeySpace = false;
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