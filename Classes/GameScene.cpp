#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

const Vec2 GRAVITY = Vec2(0, -1500.0f);

const std::string FIRST_LEVEL_NAME = "tmx/level_1.tmx";

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(GRAVITY);
	scene->getPhysicsWorld()->setDebugDrawMask(1);
	scene->getPhysicsWorld()->setSubsteps(10);

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	StartGame();

	//auto follow = Follow::create(m_player);
	//m_camera->runAction(follow->reverse());

	scheduleUpdate();

	return true;
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
	m_player = make_node<CPlayer>();
	m_player->Spawn(Vec2(200, 300));

	m_playerPuppeteer = std::make_unique<CHeroPuppeteer>();
	m_playerPuppeteer->SetPuppet(m_player);

	addChild(m_player);
}

void GameScene::SpawnEnemy()
{

}

void GameScene::SpawnItems()
{

}

void GameScene::update(float delta)
{
	//m_cameraTarget->setPosition(m_playerPuppeteer->GetPuppetPos());
}