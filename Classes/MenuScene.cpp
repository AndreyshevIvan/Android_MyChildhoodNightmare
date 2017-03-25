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
	HightlightButton();
}

void MenuScene::InitElements()
{
	auto createSprite = [=](const std::string &path, Vec2 offset) {
		auto sprite = make_node<Sprite>();
		sprite->initWithFile(path);
		SetRelativePos(sprite, offset);
		this->addChild(sprite);
	};

	createSprite(BACKGROUND_IMG, Vec2(0.5f, 0.5f));
	createSprite(NAME_BACK, GAME_NAME_OFFSET);
	createSprite(ITEMS_BACK, LEVELS_BUTTON_OFFSET);
	createSprite(GAME_NAME_IMG, GAME_NAME_OFFSET);

	auto createButton = [&](RefPtr<Label> &button, const std::string &name, Vec2 offset) {
		button = make_node<Label>();
		button->initWithTTF(name, FONT, FONT_SIZE);
		button->setColor(Color3B::WHITE);
		SetRelativePos(button, offset);
		this->addChild(button);
	};

	createButton(m_startButton, "Start", START_BUTTON_OFFSET);
	createButton(m_levelsButton, "Difficult", LEVELS_BUTTON_OFFSET);
	createButton(m_exitButton, "Leave", EXIT_BUTTON_OFFSET);
}

void MenuScene::InitListeners()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MenuScene::onTouchMoved(Touch* touch, Event* event)
{

}

bool MenuScene::onTouchBegan(Touch* touch, Event* event)
{
	if (m_touch == nullptr)
	{
		m_touch = touch;
	}

	return true;
}

void MenuScene::HightlightButton()
{
	if (m_touch != nullptr)
	{
		float dt = Director::getInstance()->getDeltaTime();
		Vec2 point = m_touch->getLocation();

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
}

void MenuScene::onTouchEnded(Touch* touch, Event* event)
{
	if (touch == m_touch)
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
		m_touch = nullptr;
	}
}

void MenuScene::GoToGame()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
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