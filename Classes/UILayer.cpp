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
	createElement(m_weaponBarPistol, PISTOL_BAR_IMG, WEAPON_BAR_OFFSET, false);
	createElement(m_weaponBarShootgun, SHOOTGUN_BAR_IMG, WEAPON_BAR_OFFSET, false);
	createElement(m_weaponBarAK, AK_BAR_IMG, WEAPON_BAR_OFFSET, false);

	auto createText = [&](RefPtr<Label> &text, Vec2 offset, int fontSize) {
		text = make_node<Label>();
		text->initWithTTF("", FONT, fontSize);
		text->setColor(Color3B::WHITE);
		text->setPosition(Vec2(winSize.width * offset.x, winSize.height * offset.y));
		this->addChild(text);
	};

	createText(m_playerHealth, HEALTH_COUNT_OFFSET, HEALTH_COUNT_SIZE);
	createText(m_playerAmmo, AMMO_COUNT_OFFSET, AMMO_COUNT_SIZE);

	m_pistolBar = std::make_shared<WeaponBar>(m_weaponBarPistol, m_playerAmmo);
	m_shootgunBar = std::make_shared<WeaponBar>(m_weaponBarShootgun, m_playerAmmo);
	m_akBar = std::make_shared<WeaponBar>(m_weaponBarAK, m_playerAmmo);
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
	for (auto touch : touches)
	{
		Vec2 point = touch->getLocation();
		bool isPause = m_buttonPause->getBoundingBox().containsPoint(point);
		DeleteTouch(touch);

		if (isPause)
		{
			Pause();
		}
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
		Vec2 point = touch->getLocation();
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
	auto leftBox = m_buttonLeft->getBoundingBox();
	auto rightBox = m_buttonRight->getBoundingBox();
	auto fireBox = m_buttonFire->getBoundingBox();

	for (auto touch : m_touches)
	{
		Vec2 point = touch->getLocation();

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
		Vec2 point = touch->getLocation();
		for (auto button : m_buttons)
		{
			hightlight_if_touch(button, point);
		}
	}
}

WeaponBar *CUILayer::GetPistolWeaponBar()
{
	return m_pistolBar.get();
}
WeaponBar *CUILayer::GetShootgunWeaponBar()
{
	return m_shootgunBar.get();
}
WeaponBar *CUILayer::GetAkWeaponBar()
{
	return m_akBar.get();
}

void CUILayer::UpdateWeaponBar(WeaponBar *weaponBar, int ammoCount)
{
	if (!weaponBar)
	{
		return;
	}

	weaponBar->SetVisible(true);
	weaponBar->SetAmmoCount(ammoCount);
}

void CUILayer::Pause()
{
	Director::getInstance()->popScene();
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