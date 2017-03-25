#include "UILayer.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char HEALTH_BAR_IMG[] = "textures/health_bar.png";
	const char AK_BAR_IMG[] = "textures/ak_bar.png";
	const char PISTOL_BAR_IMG[] = "textures/pistol_bar.png";
	const char SHOOTGUN_BAR_IMG[] = "textures/shootgun_bar.png";

	const char LEFT_BUTTON_IMG[] = "textures/left_button.png";
	const char RIGHT_BUTTON_IMG[] = "textures/right_button.png";
	const char JUMP_BUTTON_IMG[] = "textures/jump_button.png";
	const char FIRE_BUTTON_IMG[] = "textures/fire_button.png";
	const char RELOAD_BUTTON_IMG[] = "textures/reload_button.png";
	const char PAUSE_BUTTON_IMG[] = "textures/pause.png";

	const Vec2 JUMP_BUTTON_OFFSET = Vec2(0.068f, 0.347f);
	const Vec2 FIRE_BUTTON_OFFSET = Vec2(0.117f, 0.138f);
	const Vec2 RELOAD_BUTTON_OFFSET = Vec2(0.239f, 0.125f);
	const Vec2 LEFT_BUTTON_OFFSET = Vec2(0.755f, 0.136f);
	const Vec2 RIGHT_BUTTON_OFFSET = Vec2(0.906f, 0.136f);
	const Vec2 PAUSE_BUTTON_OFFSET = Vec2(0.95f, 0.93f);

	const Vec2 HEALTH_BAR_OFFSET = Vec2(0.13f, 0.82f);

	const float UNTOUCH_OPACITY = 150;
}

CUILayer *CUILayer::create(std::shared_ptr<CPlayerController> controller)
{
	CUILayer *layer = new (std::nothrow) CUILayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		layer->SetController(controller);
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return nullptr;
}

bool CUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	InitElements();
	InitListeners();

	scheduleUpdate();

	return true;
}

void CUILayer::SetController(std::shared_ptr<CPlayerController> controller)
{
	m_playerController = controller;
}

void CUILayer::update(float delta)
{
	CheckMoveButtonsTouch();
	HightlightButtons();
}

void CUILayer::InitElements()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	auto createElement = [&](RefPtr<Sprite> &button, const std::string &pathToFile, Vec2 offset, bool isButton) {
		button = make_node<Sprite>();
		button->initWithFile(pathToFile);
		button->setPosition(Vec2(winSize.width * offset.x, winSize.height * offset.y));
		this->addChild(button);
		if (isButton)
			m_buttons.push_back(button);
	};

	createElement(m_buttonJump, JUMP_BUTTON_IMG, JUMP_BUTTON_OFFSET, true);
	createElement(m_buttonFire, FIRE_BUTTON_IMG, FIRE_BUTTON_OFFSET, true);
	createElement(m_buttonReload, RELOAD_BUTTON_IMG, RELOAD_BUTTON_OFFSET, true);
	createElement(m_buttonLeft, LEFT_BUTTON_IMG, LEFT_BUTTON_OFFSET, true);
	createElement(m_buttonRight, RIGHT_BUTTON_IMG, RIGHT_BUTTON_OFFSET, true);
	createElement(m_buttonPause, PAUSE_BUTTON_IMG, PAUSE_BUTTON_OFFSET, true);

	createElement(m_healthBar, HEALTH_BAR_IMG, HEALTH_BAR_OFFSET, false);
}

void CUILayer::InitListeners()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(CUILayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CUILayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CUILayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool CUILayer::onTouchBegan(Touch* touch, Event* event)
{
	m_touches.push_back(touch);

	CheckSingleTouchButtons(touch);

	return true;
}

void CUILayer::onTouchMoved(Touch* touch, Event* event)
{

}

void CUILayer::onTouchEnded(Touch* touch, Event* event)
{
	DeleteTouch(touch);
}

void CUILayer::CheckSingleTouchButtons(Touch* touch)
{
	Vec2 point = touch->getLocation();

	auto hightlight_button = [&](RefPtr<Sprite> &button, bool isTouch) {
		float opacity = (isTouch) ? 255 : UNTOUCH_OPACITY;
		button->setOpacity(opacity);
	};
}

void CUILayer::CheckMoveButtonsTouch()
{
	auto leftBox = m_buttonLeft->getBoundingBox();
	auto rightBox = m_buttonRight->getBoundingBox();

	bool isLeftTouch = false;
	bool isRightTouch = false;

	for (auto touch : m_touches)
	{
		Vec2 point = touch->getLocation();
		isLeftTouch = leftBox.containsPoint(point);
		isRightTouch = rightBox.containsPoint(point);
	}

	m_playerController->SetMoveButtons(isLeftTouch, isRightTouch);
}

void CUILayer::HightlightButtons()
{
	for (auto button : m_buttons)
	{
		button->setOpacity(UNTOUCH_OPACITY);
	}

	auto hightlight_if_touch = [&](RefPtr<Sprite> &button, Vec2 point) {
		if (button->getBoundingBox().containsPoint(point))
		{
			button->setOpacity(255);
		}
	};

	for (auto touch : m_touches)
	{
		Vec2 point = touch->getLocation();
		for (auto button : m_buttons)
		{
			hightlight_if_touch(button, point);
		}
	}
}

void CUILayer::DeleteTouch(Touch* touch)
{
	for (auto it = m_touches.begin(); it != m_touches.end(); it++)
	{
		if (*it = touch)
		{
			m_touches.erase(it);
			break;
		}
	}
}