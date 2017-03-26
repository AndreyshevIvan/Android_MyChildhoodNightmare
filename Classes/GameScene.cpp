#include "GameScene.h"
#include <iostream>

USING_NS_CC;

const Vec2 GRAVITY = Vec2(0, -1500.0f);

const std::string FIRST_LEVEL_NAME = "tmx/level_1.tmx";

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	layer->InitCamera(scene->getDefaultCamera());
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_winSize = Director::getInstance()->getVisibleSize();

	StartGame();

	scheduleUpdate();

	return true;
}

void GameScene::InitCamera(Camera* camera)
{
	m_camera = camera;
}

void GameScene::StartGame()
{
	CreateLevel();
	SpawnPlayer();
	SpawnEnemy();
	SpawnItems();
}

void GameScene::CreateLevel()
{
	m_levelFirst = make_node<CCustomMap>(FIRST_LEVEL_NAME);
	addChild(m_levelFirst);
}

void GameScene::SpawnPlayer()
{
	m_player = make_node<CPlayer>(m_levelFirst);
	m_player->Spawn(Vec2(300, 300));

	m_playerPuppeteer = std::make_unique<CHeroPuppeteer>();
	m_playerPuppeteer->SetPuppet(m_player);
	m_playerPuppeteer->SetController(new CPlayerController());

	m_UILayer = CUILayer::create(m_playerPuppeteer->GetController());
	auto healthBar = m_UILayer->GetPlayerHealthBar();
	m_player->SetHealthBar(healthBar);

	addChild(m_player);
	addChild(m_UILayer);
}

void GameScene::SpawnEnemy()
{

}

void GameScene::SpawnItems()
{

}

void GameScene::update(float delta)
{
	UpdateCamera();
}

void GameScene::UpdateCamera()
{
	auto playerPosition = m_playerPuppeteer->GetPuppetPos();

	m_camera->setPosition(playerPosition);
	m_UILayer->setPosition(playerPosition - Vec2(m_winSize / 2));
}