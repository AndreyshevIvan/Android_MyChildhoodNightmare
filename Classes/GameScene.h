#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos_custom.h"
#include "CustomMap.h"
#include "Player.h"
#include "HeroPuppeteer.h"
#include "UILayer.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float delta) override;

	CREATE_FUNC(GameScene);

private:
	CCustomMap* m_levelFirst = nullptr;

	void StartGame();

	void CreateLevel();
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnItems();

	CPlayer* m_player = nullptr;
	CHeroPuppeteerPtr m_playerPuppeteer = nullptr;

	CUILayer* m_UILayer = nullptr;

	cocos2d::Node* m_target;
};