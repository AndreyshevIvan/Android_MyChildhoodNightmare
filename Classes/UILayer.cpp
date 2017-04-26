#include "UILayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace gameUI;

namespace
{
	const char HEALTH_BAR_IMG[] = "health_bar.png";
	const char AK_BAR_IMG[] = "ak_bar.png";
	const char PISTOL_BAR_IMG[] = "pistol_bar.png";
	const char SHOOTGUN_BAR_IMG[] = "shootgun_bar.png";

	const char LEFT_BUTTON_IMG[] = "left_button.png";
	const char RIGHT_BUTTON_IMG[] = "right_button.png";
	const char JUMP_BUTTON_IMG[] = "jump_button.png";
	const char FIRE_BUTTON_IMG[] = "fire_button.png";
	const char RELOAD_BUTTON_IMG[] = "reload_button.png";
	const char PAUSE_BUTTON_IMG[] = "pause.png";
	const char PAUSE_MENU_IMG[] = "pause_menu.png";
	const char FADE_SPRITE_IMG[] = "fade_sprite_90.png";

	const Vec2 JUMP_BUTTON_OFFSET = Vec2(0.068f, 0.347f);
	const Vec2 FIRE_BUTTON_OFFSET = Vec2(0.117f, 0.138f);
	const Vec2 RELOAD_BUTTON_OFFSET = Vec2(0.239f, 0.125f);
	const Vec2 LEFT_BUTTON_OFFSET = Vec2(0.755f, 0.136f);
	const Vec2 RIGHT_BUTTON_OFFSET = Vec2(0.906f, 0.136f);
	const Vec2 PAUSE_BUTTON_OFFSET = Vec2(0.95f, 0.93f);
	const Vec2 HEALTH_BAR_OFFSET = Vec2(0.13f, 0.82f);
	const Vec2 HEALTH_COUNT_OFFSET = Vec2(0.165f, 0.88f);
	const Vec2 WEAPON_BAR_OFFSET = Vec2(0.09f, 0.72f);
	const Vec2 RESUME_OFFSET = Vec2(0.5f, 0.49f);
	const Vec2 RESTART_OFFSET = Vec2(0.5f, 0.36f);
	const Vec2 MENU_OFFSET = Vec2(0.5f, 0.23f);

	const float UNTOUCH_OPACITY = 150;
	const float PAUSE_FADE_TIME = 0.4f;
	const float PAUSE_EASE_RATE = 6;

	const int HEALTH_COUNT_SIZE = 80;
	const int PAUSE_ITEMS_SIZE = 80;
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
	m_controllButtons = {
		m_buttonJump = CreateSprite(JUMP_BUTTON_IMG, this, JUMP_BUTTON_OFFSET),
		m_buttonFire = CreateSprite(FIRE_BUTTON_IMG, this, FIRE_BUTTON_OFFSET),
		m_buttonReload = CreateSprite(RELOAD_BUTTON_IMG, this, RELOAD_BUTTON_OFFSET),
		m_buttonLeft = CreateSprite(LEFT_BUTTON_IMG, this, LEFT_BUTTON_OFFSET),
		m_buttonRight = CreateSprite(RIGHT_BUTTON_IMG, this, RIGHT_BUTTON_OFFSET),
		m_buttonPause = CreateSprite(PAUSE_BUTTON_IMG, this, PAUSE_BUTTON_OFFSET)
	};

	auto pistolBar = CreateSprite(PISTOL_BAR_IMG, this, WEAPON_BAR_OFFSET);
	auto shootgunBar = CreateSprite(SHOOTGUN_BAR_IMG, this, WEAPON_BAR_OFFSET);
	auto akBar = CreateSprite(AK_BAR_IMG, this, WEAPON_BAR_OFFSET);
	m_pistolBar = std::make_shared<UILayer::WeaponBar>(pistolBar, this);
	m_shootgunBar = std::make_shared<UILayer::WeaponBar>(shootgunBar, this);
	m_akBar = std::make_shared<UILayer::WeaponBar>(akBar, this);

	m_healthBar = CreateSprite(HEALTH_BAR_IMG, this, HEALTH_BAR_OFFSET);
	m_playerHealth = CreateText("", FONT, HEALTH_COUNT_SIZE, this, HEALTH_COUNT_OFFSET);
	m_fadeSprite = CreateSprite(FADE_SPRITE_IMG, this, Vec2::ANCHOR_MIDDLE);
	m_pauseMenu = CreateSprite(PAUSE_MENU_IMG, this, Vec2::ANCHOR_MIDDLE);
	m_resumeButton = CreateText("Resume", FONT, PAUSE_ITEMS_SIZE, m_pauseMenu, RESUME_OFFSET);
	m_restartButton = CreateText("Restart", FONT, PAUSE_ITEMS_SIZE, m_pauseMenu, RESTART_OFFSET);
	m_menuButton = CreateText("Menu", FONT, PAUSE_ITEMS_SIZE, m_pauseMenu, MENU_OFFSET);

	auto winSize = Director::getInstance()->getWinSize();
	m_fadeSprite->setContentSize(winSize);
	m_pauseMenu->setPosition(Vec2(winSize / 2) + Vec2(0, winSize.height / 2));
	m_fadeSprite->setOpacity(0);
	m_pauseMenu->setOpacity(0);
	m_restartButton->setOpacity(0);
	m_menuButton->setOpacity(0);
	m_resumeButton->setOpacity(0);
}
void CUILayer::InitListeners()
{
	m_touchListener = EventListenerTouchAllAtOnce::create();
	m_touchListener->onTouchesBegan = CC_CALLBACK_2(CUILayer::onTouchesBegan, this);

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
void CUILayer::DeleteTouch(Touch *touch)
{
	std::remove(m_touches.begin(), m_touches.end(), touch);
}

void CUILayer::update(float delta)
{
	CheckAlwaysTouchButtons();
	HightlightButtons();
}
void CUILayer::CheckSingleTouchButtons(const vector<Touch*> &touches)
{
	if (m_isPause)
	{
		DoIfTouch(m_resumeButton, touches, CC_CALLBACK_0(CUILayer::Pause, this));

		return;
	}

	auto jump = [&]() {m_playerController->Jump(); };
	auto reload = [&]() {m_playerController->SwitchWeapon(); };

	DoIfTouch(m_buttonJump, touches, jump);
	DoIfTouch(m_buttonReload, touches, reload);
	DoIfTouch(m_buttonPause, touches, CC_CALLBACK_0(CUILayer::Pause, this));
}
void CUILayer::CheckAlwaysTouchButtons()
{
	if (m_isPause)
	{
		return;
	}

	auto moveLeft = [&]() {m_playerController->MoveLeft(); };
	auto moveRight = [&]() {m_playerController->MoveRight(); };
	auto moveFire = [&]() {m_playerController->Fire(); };

	DoIfTouch(m_buttonLeft, m_touches, moveLeft);
	DoIfTouch(m_buttonRight, m_touches, moveRight);
	DoIfTouch(m_buttonFire, m_touches, moveFire);
}
void CUILayer::HightlightButtons()
{
	if (m_isPause)
	{
		return;
	}

	for (auto button : m_controllButtons)
	{
		button->setOpacity(UNTOUCH_OPACITY);
	}

	auto hightlight_if_touch = [&](RefPtr<Sprite> &button, const Vec2 &point) {
		if (button->getBoundingBox().containsPoint(point))
		{
			button->setOpacity(gameUI::MAX_OPACITY);
		}
	};

	for (auto touch : m_touches)
	{
		const Vec2 &point = touch->getLocation();
		for (auto button : m_controllButtons)
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

void CUILayer::Pause()
{
	m_isPause = !m_isPause;
	onPause(m_isPause);

	const Vec2 winCenter = Director::getInstance()->getWinSize() / 2;
	const Vec2 menuPos = (m_isPause) ? winCenter : winCenter + Vec2(0, winCenter.y);
	auto openAction = MoveTo::create(PAUSE_FADE_TIME, menuPos);
	ActionEase* openActionWithEase = EaseIn::create(openAction, PAUSE_EASE_RATE);
	FadeTo* fade = FadeOut::create(PAUSE_FADE_TIME);

	if (m_isPause)
	{
		fade = FadeIn::create(PAUSE_FADE_TIME);
		openActionWithEase = EaseOut::create(openAction, PAUSE_EASE_RATE);
	}

	m_pauseMenu->stopAllActions();
	m_pauseMenu->runAction(openActionWithEase);
	m_pauseMenu->runAction(fade->clone());
	m_restartButton->runAction(fade->clone());
	m_menuButton->runAction(fade->clone());
	m_resumeButton->runAction(fade->clone());
	m_fadeSprite->runAction(fade->clone());
	std::for_each(m_controllButtons.begin(), m_controllButtons.end(), [&](GameSprite &button) {
		button->runAction(fade->clone());
	});
}

GameText CUILayer::GetPlayerHealthBar()
{
	return m_playerHealth;
}

void CUILayer::cleanup()
{
	unscheduleUpdate();
	removeAllChildren();
	_eventDispatcher->removeEventListener(m_touchListener);
}