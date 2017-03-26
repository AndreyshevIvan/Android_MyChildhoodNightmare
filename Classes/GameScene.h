#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos_custom.h"
#include "CustomMap.h"
#include "Player.h"
#include "HeroPuppeteer.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void update(float delta) override;

	CREATE_FUNC(GameScene);

private:
	void InitCamera(cocos2d::Camera* camera);
	void StartGame();

	void CreateLevel();
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnItems();

	void UpdateCamera();

	cocos2d::Size m_winSize;

	cocos2d::Camera *m_camera = nullptr;
	CCustomMap *m_levelFirst = nullptr;
	CPlayer *m_player = nullptr;
	CHeroPuppeteerPtr m_playerPuppeteer = nullptr;

	CUILayer *m_UILayer = nullptr;

	cocos2d::Node *m_target;
};