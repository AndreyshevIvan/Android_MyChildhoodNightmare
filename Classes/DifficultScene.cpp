#include "DifficultScene.h"
#include "MenuScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;
using namespace gameUI;

namespace
{
	const char BACKGROUND_IMG[] = "menu_wrapper.png";
	const char TITLE_IMG[] = "difficult_title.png";

	const Vec2 DIFFICULT_TITLE_OFFSET = Vec2(0.5f, 0.8f);
	const Vec2 EASY_ITEM_OFFSET = Vec2(0.5f, 0.26f);
	const Vec2 NORMAL_ITEM_OFFSET = Vec2(0.5f, 0.4f);
	const Vec2 HARD_ITEM_OFFSET = Vec2(0.5f, 0.54f);
}

Scene* DifficultScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DifficultScene::create();
	scene->addChild(layer);

	return scene;
}

bool DifficultScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitElements();
	InitListener();
	InitEvents();

	return true;
}

void DifficultScene::InitElements()
{
	CreateSprite(BACKGROUND_IMG, this, Vec2::ANCHOR_MIDDLE);
	CreateSprite(TITLE_IMG, this, DIFFICULT_TITLE_OFFSET);

	m_buttons = {
		m_easyButton = CreateText("Easy", FONT, MENU_LARGE_FONT_SIZE, this, EASY_ITEM_OFFSET),
		m_normalButton = CreateText("Normal", FONT, MENU_LARGE_FONT_SIZE, this, NORMAL_ITEM_OFFSET),
		m_hardButton = CreateText("Hard", FONT, MENU_LARGE_FONT_SIZE, this, HARD_ITEM_OFFSET)
	};

}
void DifficultScene::InitListener()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DifficultScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}
void DifficultScene::InitEvents()
{

}

bool DifficultScene::onTouchBegan(Touch* touch, Event* event)
{
	auto highLight = ScaleTo::create(SCENE_TRANSITION_TIME, BUTTONS_SCALE_FACTOR);
	
	auto setEasy = [&]() {
		CDataController::SetDifficult(Difficult::EASY);
		m_easyButton->runAction(highLight);
		SetMenuScene();
	};
	auto setNormal = [&]() {
		CDataController::SetDifficult(Difficult::NORMAL);
		m_normalButton->runAction(highLight);
		SetMenuScene();
	};
	auto setHard = [&]() {
		CDataController::SetDifficult(Difficult::HARD);
		m_hardButton->runAction(highLight);
		SetMenuScene();
	};

	DoIfTouch(m_easyButton, { touch }, setEasy);
	DoIfTouch(m_normalButton, { touch }, setNormal);
	DoIfTouch(m_hardButton, { touch }, setHard);

	return true;
}

void DifficultScene::SetMenuScene()
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));
}

void DifficultScene::cleanup()
{
	removeAllChildren();
	_eventDispatcher->removeEventListener(m_touchListener);
}