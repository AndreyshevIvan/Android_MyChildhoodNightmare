#include "MenuScene.h"
#include "DifficultScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;
using namespace std;
using namespace gameUI;

namespace
{
	const char FADE_SPRITE_IMG[] = "fade_sprite.png";
	const char BACKGROUND_IMG[] = "menu_wrapper.png";
	const char GAME_NAME_IMG[] = "game_name.png";
	const char NAME_BACK[] = "name_back.png";
	const char ITEMS_BACK[] = "items_back.png";
	const char LEAVE_BACK[] = "leave_back.png";

	const float FONT_HIGHTLIGHT_SCALE = 1.2f;

	const Vec2 GAME_NAME_OFFSET = Vec2(0.5f, 0.78f);
	const Vec2 START_BUTTON_OFFSET = Vec2(0.5f, 0.46f);
	const Vec2 LEVELS_BUTTON_OFFSET = Vec2(0.5f, 0.28f);
	const Vec2 EXIT_BUTTON_OFFSET = Vec2(0.91f, 0.1f);
	const Vec2 ITEMS_BACK_OFFSET = Vec2(0.5f, 0.36f);
}

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitElements();
	InitListeners();

	scheduleUpdate();

	return true;
}

void MenuScene::update(float delta)
{

}

void MenuScene::InitElements()
{
	CreateSprite(BACKGROUND_IMG, this, Vec2::ANCHOR_MIDDLE);
	CreateSprite(NAME_BACK, this, GAME_NAME_OFFSET);
	CreateSprite(ITEMS_BACK, this, ITEMS_BACK_OFFSET);
	CreateSprite(GAME_NAME_IMG, this, GAME_NAME_OFFSET);
	CreateSprite(LEAVE_BACK, this, EXIT_BUTTON_OFFSET);

	m_startButton = CreateText("Start", FONT, MENU_LARGE_FONT_SIZE, this, START_BUTTON_OFFSET);
	m_levelsButton = CreateText("Difficult", FONT, MENU_LARGE_FONT_SIZE, this, LEVELS_BUTTON_OFFSET);
	m_exitButton = CreateText("Leave", FONT, MENU_SMALL_FONT_SIZE, this, EXIT_BUTTON_OFFSET);

	auto winSize = Director::getInstance()->getWinSize();
	m_fadeSprite = CreateSprite(FADE_SPRITE_IMG, this, Vec2::ANCHOR_MIDDLE);
	m_fadeSprite->setContentSize(winSize);
	m_fadeSprite->setOpacity(0);
}

void MenuScene::InitListeners()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}

bool MenuScene::onTouchBegan(Touch* touch, Event* event)
{
	if (m_state != MenuState::NONE)
	{
		return false;
	}

	auto highLightButton = ScaleTo::create(SCENE_TRANSITION_TIME, BUTTONS_SCALE_FACTOR);

	auto start = [&]() {
		m_startButton->runAction(highLightButton);
		m_state = MenuState::WAIT_EVENT;
		SetGameScene();
	};
	auto chooseLevel = [&]() {
		m_levelsButton->runAction(highLightButton);
		m_state = MenuState::WAIT_EVENT;
		SetDifficulScene();
	};
	auto exitGame = [&]() {
		m_exitButton->runAction(highLightButton);
		m_state = MenuState::WAIT_EVENT;
		CloseApp();
	};

	DoIfTouch(m_startButton, { touch }, start);
	DoIfTouch(m_levelsButton, { touch }, chooseLevel);
	DoIfTouch(m_exitButton, { touch }, exitGame);

	return true;
}

void MenuScene::onTouchEnded(Touch* touch, Event* event)
{
}

void MenuScene::SetGameScene()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));
}

void MenuScene::SetDifficulScene()
{
	auto scene = DifficultScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));
}

void MenuScene::CloseApp()
{
	const float fadeTime = SCENE_TRANSITION_TIME / 2;

	auto exit = []() {
		Director::getInstance()->end();
	};
	auto startFade = [&]() {
		auto fadeAction = FadeIn::create(fadeTime);
		m_fadeSprite->runAction(fadeAction);
	};

	auto exitEvents = Sequence::create(
		CallFunc::create(startFade),
		DelayTime::create(fadeTime),
		CallFunc::create(exit),
		nullptr
	);

	runAction(exitEvents);
}

void MenuScene::cleanup()
{
	unscheduleUpdate();
	_eventDispatcher->removeEventListener(m_touchListener);
}