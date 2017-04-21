#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;
using namespace std;

namespace
{
	const char FADE_SPRITE_IMG[] = "textures/fade_sprite.png";
	const char BACKGROUND_IMG[] = "textures/menu_wrapper.png";
	const char GAME_NAME_IMG[] = "textures/game_name.png";
	const char NAME_BACK[] = "textures/name_back.png";
	const char ITEMS_BACK[] = "textures/items_back.png";
	const char LEAVE_BACK[] = "textures/leave_back.png";
	const char FONT[] = "fonts/nightmarealley.ttf";

	const int START_BUTTON_FONT_SIZE = 120;
	const int FONT_SIZE = 100;
	const int EXIT_FONT_SIZE = 66;
	const float FONT_HIGHTLIGHT_SCALE = 1.2f;

	const Vec2 GAME_NAME_OFFSET = Vec2(0.5f, 0.78f);
	const Vec2 START_BUTTON_OFFSET = Vec2(0.5f, 0.46f);
	const Vec2 LEVELS_BUTTON_OFFSET = Vec2(0.5f, 0.28f);
	const Vec2 EXIT_BUTTON_OFFSET = Vec2(0.91f, 0.1f);
	const Vec2 ITEMS_BACK_OFFSET = Vec2(0.5f, 0.36f);

	const float BUTTONS_SCALE_TIME = 0.8f;
	const float BUTTONS_SCALE_FACTOR = 1.6f;
	const float SCENE_TRANSITION_TIME = 1.4f;
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
	auto winSize = Director::getInstance()->getWinSize();

	/*
	auto createSprite = [=](const string &path, Node* parent, Vec2 offset = Vec2(0.5, 0.5)) {
		auto sprite = make_node<Sprite>();
		sprite->initWithFile(path);
		SetRelativePos(sprite, offset);
		parent->addChild(sprite);
		return sprite;
	};*/

	GameUI::CreateSprite(BACKGROUND_IMG, this, Vec2::ANCHOR_MIDDLE);
	GameUI::CreateSprite(NAME_BACK, this, GAME_NAME_OFFSET);
	GameUI::CreateSprite(ITEMS_BACK, this, ITEMS_BACK_OFFSET);
	GameUI::CreateSprite(GAME_NAME_IMG, this, GAME_NAME_OFFSET);
	GameUI::CreateSprite(LEAVE_BACK, this, EXIT_BUTTON_OFFSET);

	/*
	auto createButton = [&](RefPtr<Label> &button, const string &name, Vec2 offset, int fontSize = FONT_SIZE) {
		button = make_node<Label>();
		button->initWithTTF(name, FONT, fontSize);
		button->enableOutline(Color4B::BLACK, 1);
		button->setColor(Color3B::WHITE);
		SetRelativePos(button, offset);
		this->addChild(button);
	};*/

	m_startButton = GameUI::CreateMenuItem("Start", FONT, START_BUTTON_FONT_SIZE, this, START_BUTTON_OFFSET);
	m_levelsButton = GameUI::CreateMenuItem("Difficult", FONT, START_BUTTON_FONT_SIZE, this, LEVELS_BUTTON_OFFSET);
	m_exitButton = GameUI::CreateMenuItem("Leave", FONT, EXIT_FONT_SIZE, this, EXIT_BUTTON_OFFSET);

	m_fadeSprite = GameUI::CreateSprite(FADE_SPRITE_IMG, this, Vec2::ANCHOR_MIDDLE);
	m_fadeSprite->setContentSize(winSize);
	m_fadeSprite->setOpacity(0);
}

void MenuScene::InitListeners()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}

void MenuScene::onTouchMoved(Touch* touch, Event* event)
{
}

bool MenuScene::onTouchBegan(Touch* touch, Event* event)
{
	if (m_state != MenuState::NONE)
	{
		return false;
	}

	const Vec2 touchPoint = touch->getLocation();
	
	auto start_event_if_touch = [&](RefPtr<Label> &button, std::function<void()> onTouch) {
		if (!button->getBoundingBox().containsPoint(touchPoint))
		{
			return;
		}

		auto highLight = ScaleTo::create(BUTTONS_SCALE_TIME, BUTTONS_SCALE_FACTOR);
		auto onTouchEvent = Sequence::create(CallFunc::create(onTouch), nullptr);
		button->runAction(highLight);
		runAction(onTouchEvent);
		m_state = MenuState::WAIT_EVENT;
	};

	start_event_if_touch(m_startButton, CC_CALLBACK_0(MenuScene::GoToGame, this));
	start_event_if_touch(m_exitButton, CC_CALLBACK_0(MenuScene::CloseApp, this));

	return true;
}

void MenuScene::onTouchEnded(Touch* touch, Event* event)
{
}

void MenuScene::GoToGame()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));
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