#include "GameScene.h"
#include <iostream>

USING_NS_CC;

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
	SpawnEnemies();
	SpawnItems();
	CreateUI();
}

void GameScene::CreateLevel()
{
	m_levelFirst = make_node<CCustomMap>(FIRST_LEVEL_NAME);
	addChild(m_levelFirst);
}
void GameScene::SpawnPlayer()
{
	m_player = make_node<CPlayer>(m_levelFirst);
	m_player->Spawn(m_levelFirst->GetHeroWorldPosition());

	m_playerPuppeteer = std::make_unique<CHeroPuppeteer>();
	m_playerPuppeteer->SetPuppet(m_player);
	m_playerPuppeteer->SetController(new CPlayerController());

	addChild(m_player);
}
void GameScene::SpawnEnemies()
{
	auto positions = m_levelFirst->GetEnemyWorldPositions();

	for (auto pos : positions)
	{
		auto enemy = make_node<CEnemy>(m_levelFirst);
		m_enemies.push_back(enemy);
		enemy->Spawn(pos);
		m_levelFirst->AddEnemy(enemy);

		auto enemyPuppeteer = std::make_shared<CEnemyPuppeteer>();
		enemyPuppeteer->SetPuppet(enemy);
		m_enemiesPuppeeters.push_back(enemyPuppeteer);

		addChild(enemy);
	}
}
void GameScene::SpawnItems()
{

}
void GameScene::CreateUI()
{
	m_UILayer = CUILayer::create(m_playerPuppeteer->GetController());

	auto healthBar = m_UILayer->GetPlayerHealthBar();
	auto pistolBar = m_UILayer->GetPistolWeaponBar();
	auto shootgunBar = m_UILayer->GetShootgunWeaponBar();
	auto akBar = m_UILayer->GetAkWeaponBar();

	m_player->SetHealthBar(healthBar);
	m_player->InitWeaponBars(pistolBar, shootgunBar, akBar);

	addChild(m_UILayer);
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