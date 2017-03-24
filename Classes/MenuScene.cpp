#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char BACKGROUND_IMG[] = "textures/menu_wrapper.png";
	const char GAME_NAME_IMG[] = "textures/game_name.png";
	const char NAME_BACK[] = "textures/name_back.png";
	const char ITEMS_BACK[] = "textures/items_back.png";
	const char FONT[] = "fonts/nightmarealley.ttf";

	const int FONT_SIZE = 100;
	const float FONT_HIGHTLIGHT_SCALE = 1.2f;

	const Vec2 GAME_NAME_OFFSET = Vec2(0.5f, 0.78f);
	const Vec2 START_BUTTON_OFFSET = Vec2(0.5f, 0.46f);
	const Vec2 LEVELS_BUTTON_OFFSET = Vec2(0.5f, 0.30f);
	const Vec2 EXIT_BUTTON_OFFSET = Vec2(0.5f, 0.14f);
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
	m_background = make_node<Sprite>();
	m_background->initWithFile(BACKGROUND_IMG);
	SetRelativePos(m_background, Vec2(0.5f, 0.5f));

	m_gameName = make_node<Sprite>();
	m_gameName->initWithFile(GAME_NAME_IMG);
	SetRelativePos(m_gameName, GAME_NAME_OFFSET);

	m_nameBack = make_node<Sprite>();
	m_nameBack->initWithFile(NAME_BACK);
	SetRelativePos(m_nameBack, GAME_NAME_OFFSET);

	m_itemsBack = make_node<Sprite>();
	m_itemsBack->initWithFile(ITEMS_BACK);
	SetRelativePos(m_itemsBack, LEVELS_BUTTON_OFFSET);

	m_startButton = make_node<Label>();
	m_startButton->initWithTTF("Start", FONT, FONT_SIZE);
	m_startButton->setColor(Color3B::WHITE);
	SetRelativePos(m_startButton, START_BUTTON_OFFSET);

	m_levelsButton = make_node<Label>();
	m_levelsButton->initWithTTF("Difficult", FONT, FONT_SIZE);
	m_levelsButton->setColor(Color3B::WHITE);
	SetRelativePos(m_levelsButton, LEVELS_BUTTON_OFFSET);

	m_exitButton = make_node<Label>();
	m_exitButton->initWithTTF("Leave", FONT, FONT_SIZE);
	m_exitButton->setColor(Color3B::WHITE);
	SetRelativePos(m_exitButton, EXIT_BUTTON_OFFSET);

	addChild(m_background);
	addChild(m_nameBack);
	addChild(m_gameName);
	addChild(m_itemsBack);
	addChild(m_startButton);
	addChild(m_levelsButton);
	addChild(m_exitButton);
}

void MenuScene::InitListeners()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);

	auto exitListener = EventListenerKeyboard::create();
	exitListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(exitListener, this);
}

void MenuScene::GoToGame()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		CloseApp();
	}
}

void MenuScene::onTouchMoved(Touch* touch, Event* event)
{
	HightlightButton(touch);
}

bool MenuScene::onTouchBegan(Touch* touch, Event* event)
{
	HightlightButton(touch);

	return true;
}

void MenuScene::HightlightButton(Touch* touch)
{
	float dt = Director::getInstance()->getDeltaTime();
	Vec2 point = touch->getLocation();

	auto highlight_if = [&](RefPtr<Label> button) {
		float scale = button->getScale();
		if (button->getBoundingBox().containsPoint(point) && scale < FONT_HIGHTLIGHT_SCALE)
		{
			button->setScale(scale + 1 * dt);
		}
		else if (!button->getBoundingBox().containsPoint(point) && scale > 1)
		{
			button->setScale(scale - 1 * dt);
		}
	};

	highlight_if(m_startButton);
	highlight_if(m_levelsButton);
	highlight_if(m_exitButton);
}

void MenuScene::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 point = touch->getPreviousLocation();

	auto isTouchButton = [&](RefPtr<Label> button) {
		return button->getBoundingBox().containsPoint(point);
	};

	if (isTouchButton(m_startButton))
	{
		GoToGame();
	}
	if (isTouchButton(m_levelsButton))
	{

	}
	if (isTouchButton(m_exitButton))
	{
		CloseApp();
	}

	m_startButton->setScale(1);
	m_levelsButton->setScale(1);
	m_exitButton->setScale(1);
}

void MenuScene::CloseApp()
{
	Director::getInstance()->end();
}

template<class T>
void MenuScene::SetRelativePos(cocos2d::RefPtr<T> element, const cocos2d::Vec2 &offset)
{
	auto winSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 position = cocos2d::Vec2(winSize.width * offset.x, winSize.height * offset.y);
	element->setPosition(position);
}