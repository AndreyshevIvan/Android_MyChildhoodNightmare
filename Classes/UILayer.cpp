#include "UILayer.h"
#include "GameUI.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <string>

USING_NS_CC;
using namespace std;

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
	const Vec2 HEALTH_COUNT_OFFSET = Vec2(0.165f, 0.88f);
	const Vec2 WEAPON_BAR_OFFSET = Vec2(0.09f, 0.72f);
	const Vec2 AMMO_COUNT_OFFSET = Vec2(0.131f, 0.68f);

	const float UNTOUCH_OPACITY = 150;

	const char FONT[] = "fonts/nightmarealley.ttf";
	const int HEALTH_COUNT_SIZE = 80;
	const int AMMO_COUNT_SIZE = 40;
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

void CUILayer::InitElements()
{
	m_buttons = {
		m_buttonJump = GameUI::CreateSprite(JUMP_BUTTON_IMG, this, JUMP_BUTTON_OFFSET),
		m_buttonFire = GameUI::CreateSprite(FIRE_BUTTON_IMG, this, FIRE_BUTTON_OFFSET),
		m_buttonReload = GameUI::CreateSprite(RELOAD_BUTTON_IMG, this, RELOAD_BUTTON_OFFSET),
		m_buttonLeft = GameUI::CreateSprite(LEFT_BUTTON_IMG, this, LEFT_BUTTON_OFFSET),
		m_buttonRight = GameUI::CreateSprite(RIGHT_BUTTON_IMG, this, RIGHT_BUTTON_OFFSET),
		m_buttonPause = GameUI::CreateSprite(PAUSE_BUTTON_IMG, this, PAUSE_BUTTON_OFFSET),
		m_healthBar = GameUI::CreateSprite(HEALTH_BAR_IMG, this, HEALTH_BAR_OFFSET)
	};

	m_playerHealth = GameUI::CreateMenuItem("", FONT, HEALTH_COUNT_SIZE, this, HEALTH_COUNT_OFFSET);
	m_playerAmmo = GameUI::CreateMenuItem("", FONT, AMMO_COUNT_SIZE, this, AMMO_COUNT_OFFSET);

	auto pistolBar = GameUI::CreateSprite(PISTOL_BAR_IMG, this, WEAPON_BAR_OFFSET);
	auto shootgunBar = GameUI::CreateSprite(SHOOTGUN_BAR_IMG, this, WEAPON_BAR_OFFSET);
	auto akBar = GameUI::CreateSprite(AK_BAR_IMG, this, WEAPON_BAR_OFFSET);
	m_pistolBar = std::make_shared<UILayer::WeaponBar>(pistolBar, m_playerAmmo);
	m_shootgunBar = std::make_shared<UILayer::WeaponBar>(shootgunBar, m_playerAmmo);
	m_akBar = std::make_shared<UILayer::WeaponBar>(akBar, m_playerAmmo);
}
void CUILayer::InitListeners()
{
	m_touchListener = EventListenerTouchAllAtOnce::create();
	m_touchListener->onTouchesBegan = CC_CALLBACK_2(CUILayer::onTouchesBegan, this);
	m_touchListener->onTouchesMoved = CC_CALLBACK_2(CUILayer::onTouchesMoved, this);
	m_touchListener->onTouchesEnded = CC_CALLBACK_2(CUILayer::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}

void CUILayer::onTouchesBegan(const std::vector<Touch*> &touches, Event* event)
{
	CheckSingleTouchButtons(touches);

	for (auto touch : touches)
	{
		m_touches.push_back(touch);
	}
}
void CUILayer::onTouchesMoved(const std::vector<Touch*> &touches, Event* event)
{
	(void)touches;
	(void)event;
}
void CUILayer::onTouchesEnded(const std::vector<Touch*> &touches, Event* event)
{
	(void)event;
	for (auto touch : touches)
	{
		const Vec2 &point = touch->getLocation();
		bool isPause = m_buttonPause->getBoundingBox().containsPoint(point);
		DeleteTouch(touch);
		Pause(isPause);
	}
}
void CUILayer::DeleteTouch(Touch *touch)
{
	std::remove(m_touches.begin(), m_touches.end(), touch);
}

void CUILayer::update(float delta)
{
	CheckAlwaysTouchButtons();
	HightlightButtons();
}
void CUILayer::CheckSingleTouchButtons(const std::vector<Touch*> &touches)
{
	for (auto touch : touches)
	{
		const Vec2 &point = touch->getLocation();
		bool isJump = m_buttonJump->getBoundingBox().containsPoint(point);
		bool isReload = m_buttonReload->getBoundingBox().containsPoint(point);

		if (isJump)
		{
			m_playerController->Jump();
		}
		if (isReload)
		{
			m_playerController->Reload();
		}
	}
}
void CUILayer::CheckAlwaysTouchButtons()
{
	const Rect &leftBox = m_buttonLeft->getBoundingBox();
	const Rect &rightBox = m_buttonRight->getBoundingBox();
	const Rect &fireBox = m_buttonFire->getBoundingBox();

	for (auto touch : m_touches)
	{
		const Vec2 &point = touch->getLocation();

		if (leftBox.containsPoint(point))
		{
			m_playerController->MoveLeft();
		}
		if (rightBox.containsPoint(point))
		{
			m_playerController->MoveRight();
		}
		if (fireBox.containsPoint(point))
		{
			m_playerController->Fire();
		}
	}
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
		const Vec2 &point = touch->getLocation();
		for (auto button : m_buttons)
		{
			hightlight_if_touch(button, point);
		}
	}
}

UILayer::WeaponBar *CUILayer::GetPistolWeaponBar()
{
	return m_pistolBar.get();
}
UILayer::WeaponBar *CUILayer::GetShootgunWeaponBar()
{
	return m_shootgunBar.get();
}
UILayer::WeaponBar *CUILayer::GetAkWeaponBar()
{
	return m_akBar.get();
}

void CUILayer::Pause(bool isPause)
{
	onPause(isPause);

	// open-close pause menu
}

cocos2d::RefPtr<cocos2d::Label> CUILayer::GetPlayerHealthBar()
{
	return m_playerHealth;
}

void CUILayer::cleanup()
{
	unscheduleUpdate();
	_eventDispatcher->removeEventListener(m_touchListener);
}